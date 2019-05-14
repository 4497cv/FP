
#include "simon_says.h"

static uint8_t buffer_sequence[SIMON_SEQUENCE] = {0};
static boolean_t sequence_complete_g;
static uint8_t current_key;
static uint8_t prev_key;
static boolean_t key_flag;
static uint8_t sequence_number;
static booleant_t timeout_status_flag = FALSE;
static NoteBuffer_t current_state;
static uint8_t seconds_g = 0;

sequence_map_t sequence_map[SEQUENCE_SIZE] =
{
	{SEQUENCE_ZERO,		{C, D, E, G, A}},
	{SEQUENCE_ONE,		{D, G, A, C, C}},
	{SEQUENCE_TWO,		{A, G, B, C, D}},
	{SEQUENCE_THREE,	{D, G, D, C, A}},
	{SEQUENCE_FOUR,		{A, B, A, B, C}},
	{SEQUENCE_FIVE,		{D, B, E, G, A}},
	{SEQUENCE_SIX,		{A, D, A, G, A}},
	{SEQUENCE_SEVEN,	{C, A, G, A, D}}
};

static FSM_SS_t FSM_Buffer[5]=
{
	{&buffer_sequence[0],   {buffer_S2,  buffer_S3, buffer_S4, buffer_S5, buffer_S1}},
	{&buffer_sequence[1],   {buffer_S3,  buffer_S4, buffer_S5, buffer_S1, buffer_S2}},
	{&buffer_sequence[2],   {buffer_S4,  buffer_S5, buffer_S1, buffer_S2, buffer_S3}},
	{&buffer_sequence[3],   {buffer_S5,  buffer_S1, buffer_S2, buffer_S3, buffer_S4}},
	{&buffer_sequence[4],   {buffer_S1,  buffer_S2, buffer_S3, buffer_S4, buffer_S5}}
};

static TERM_playnotes_t FSM_term_playnotes[5]=
{
	{terminal_playnote1,   {buffer_S2,  buffer_S3, buffer_S4, buffer_S5, buffer_S1}},
	{terminal_playnote2,   {buffer_S3,  buffer_S4, buffer_S5, buffer_S1, buffer_S2}},
	{terminal_playnote3,   {buffer_S4,  buffer_S5, buffer_S1, buffer_S2, buffer_S3}},
	{terminal_playnote4,   {buffer_S5,  buffer_S1, buffer_S2, buffer_S3, buffer_S4}},
	{terminal_playnote5,   {buffer_S1,  buffer_S2, buffer_S3, buffer_S4, buffer_S5}}
};

void generate_sequence_buffer(void)
{
    sequence_number = FTM_get_counter_reg();
	sequence_complete_g = FALSE;

	printf("Sequence #%d:\n", sequence_number);

	/* Update current global buffer */
	get_sequence(sequence_number);

	/* Enable PIT #0 interrupt */
	PIT_enable_interrupt(PIT_0);
	/* Enable PIT #1 interrupt */
	PIT_enable_interrupt(PIT_1);
}

void get_sequence(uint8_t sequence_index)
{
	uint8_t i;

	for(i = 0; BUFFER_SIZE > i ; i++)
	{
		/* update buffer sequence to global buffer */
		buffer_sequence[i] = sequence_map[sequence_index].sequence_buffer[i];
	}
}

void send_sequence_buzzer(void)
{
	static uint8_t index;
	boolean_t pit_status;

	pit_status = PIT_get_interrupt_flag_status(PIT_0);

	if(TRUE == pit_status)
	{
		note_frequency(buffer_sequence[index]);
		index++;
		if(BUFFER_LIMIT == index)
		{
			index = 0;
			/* disable PIT #0 interrupt */
			PIT_disable_interrupt(PIT_0);
			/* disable PIT #1 interrupt */
			PIT_disable_interrupt(PIT_1);

			GPIO_clear_pin(GPIO_C,bit_5);

			SS_handle_user_input();
		}
		else
		{
			/* shut down buzzer */
			GPIO_clear_pin(GPIO_C,bit_5);
		}
	}
}

void handle_time_interrupt(void)
{
	boolean_t victory_flag;
	uint8_t key_number;
	uint8_t current_key;
	uint8_t note_index;

	/* get note found flag status */
	note_found_flag = get_note_found_flag();

	if(note_found_flag)
	{
		/* send victory message to SPI */
		terminal_correct_msg();
		/* get game's next state status */
		current_state = FSM_Buffer[current_state].next[0];
		/* indicate that the user has won */
		victory_flag = TRUE;
	}
	else
	{
		/* indicate that the user has lost */
		victory_flag = FALSE;
	}

	if((TRUE == victory_flag) && (FALSE == timeout_status_flag))
	{
		/* send victory message to SPI */	
		terminal_victory_msg();
	}
	else if((FALSE == victory_flag) && (TRUE == timeout_status_flag))
	{
		/* send losing message to SPI */
		terminal_game_over_msg();
	}
	else
	{
		/* increment seconds */
		seconds_g++;
		update_timeout_status_flag();
	}
}

void update_timeout_status_flag(void)
{
	if(TIME_LIMIT == seconds_g)
	{
		timeout_status_flag = TRUE;
	}
	else
	{
		timeout_status_flag = FALSE;
	}	
}