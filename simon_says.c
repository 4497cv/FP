
#include "simon_says.h"

//#define DEBUG

static uint8_t buffer_sequence[SIMON_SEQUENCE] = {0};
static boolean_t sequence_complete_g;
static uint8_t current_key;
static uint8_t prev_key;
static boolean_t key_flag;

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

void generate_sequence_buffer(void)
{
	uint8_t sequence_number;
 
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
		/* sequence */
		buffer_sequence[i] = sequence_map[sequence_index].sequence_buffer[i];
#ifdef DEBUG
		printf("%c\n",buffer_sequence[i]);
#endif
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

void SS_handle_user_input(void)
{
	NoteBuffer_t current_state;
	boolean_t correct_flag;
	uint8_t key_number;
	uint8_t current_key;
	uint8_t note_index;

	correct_flag = FALSE;
	current_state = buffer_S1;
	note_index = 1;

	do
	{
		/* wait until voltage drops to zero */
		FREQ_voltage_drop();

#ifdef DEBUG
		printf("Play note #%i\n", note_index);
#endif

		key_flag = FREQ_get_current_note(*FSM_Buffer[current_state].key_number);

		if(key_flag)
		{
			/* send victory message to SPI */
#ifdef DEBUG
			printf("Correct!\n");
#endif
			/* get buffer's next state */
			current_state = FSM_Buffer[current_state].next[0];
			correct_flag = TRUE;
		}
		else
		{
			correct_flag = FALSE;
			current_state = buffer_S1;
		}
		note_index++;
	}while(buffer_S1 != current_state);


	if(TRUE == correct_flag)
	{
		/* Send victory message to SPI */
#ifdef DEBUG
		printf("YOU WON!\n");
#endif
	}
	else
	{
		/* Send losing message to SPI */
#ifdef DEBUG
		printf("GAME OVER\n");
#endif
	}
}

uint8_t SS_note_convert_to_number(uint8_t keynote)
{
	uint8_t key_number;
	switch(keynote)
	{
		case 'C':
			key_number = DO;
		break;
		case 'D':
			key_number = RE;
		break;
		case 'E':
			key_number = MI;
		break;
		case 'G':
			key_number = SOL;
		break;
		case 'A':
			key_number = LA;
		break;
	}

	return key_number;
}
