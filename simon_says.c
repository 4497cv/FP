
#include "simon_says.h"

static uint8_t buffer_sequence[SIMON_SEQUENCE] = {0};
static boolean_t sequence_complete_g;
static uint8_t current_key;
static uint8_t prev_key;
static boolean_t key_flag;
static uint8_t sequence_number;
static boolean_t timeout_status_flag = FALSE;
static NoteBuffer_t current_state = buffer_S1;
static volatile uint8_t seconds_g = 0;
static volatile uint8_t time_g = 0;
static boolean_t buzzer_end_flag;

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

	/* Update current global buffer */
	get_sequence(sequence_number);
}

void play_sequence()
{
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
		}
		else
		{
			/* shut down buzzer */
			GPIO_clear_pin(GPIO_C,bit_5);
		}
	}
}

boolean_t get_buzzer_end_flag_status(void)
{
	return buzzer_end_flag;
}

void handle_time_interrupt(void)
{
	boolean_t victory_flag;
	boolean_t note_found_flag;
	update_current_note(*FSM_Buffer[current_state].key_number);
	LCD_set_pentagram_sequence(sequence_number, current_state);
	/* get note found flag status */
	note_found_flag = get_note_found_flag();

	if(note_found_flag)
	{
		/* send victory message to SPI */
		terminal_correct_msg();
		LCD_set_pentagram_sequence(sequence_number, *FSM_Buffer[current_state].key_number);
		/* get game's next state status */
		current_state = FSM_Buffer[current_state].next[0];
		/* reset seconds */
		seconds_g = 0;
		/* indicate that the user has won */
		if(current_state == buffer_S1)
		{
			victory_flag = TRUE;
		}

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
		/* start PIT for adc sampling @ 2kHz */
		PIT_disable_interrupt(PIT_2);
		/* start pit for time interrupt handler */
		PIT_disable_interrupt(PIT_3);
		terminal_enter_your_initials();
		system_user_record_capture(time_g);

	}
	else if((FALSE == victory_flag) && (TRUE == timeout_status_flag))
	{
		/* send losing message to SPI */
		terminal_game_over_msg();
		/* start PIT for adc sampling @ 2kHz */
		PIT_disable_interrupt(PIT_2);
		/* start pit for time interrupt handler */
		PIT_disable_interrupt(PIT_3);
		set_playerboard_flag();
		terminal_enter_your_initials();
		system_user_record_capture(time_g);
	}
	else
	{
		/* increment seconds */
		time_g++;
		seconds_g++;
		update_timeout_status_flag();
	}
}

void update_timeout_status_flag(void)
{
	if(TIME_LIMIT == seconds_g)
	{
		/* indicate time out if it reached its limit */
		timeout_status_flag = TRUE;
	}
	else
	{
		/* indicate time has not run out */
		timeout_status_flag = FALSE;
	}	
}

void victory_sound()
{
	static uint8_t index;
	boolean_t pit_status;

	pit_status = PIT_get_interrupt_flag_status(PIT_0);

	if(TRUE == pit_status)
	{
		note_frequency(0.0001);
		index++;
		if(1 == index)
		{
			index = 0;
			/* disable PIT #0 interrupt */
			PIT_disable_interrupt(PIT_0);
			/* disable PIT #1 interrupt */
			PIT_disable_interrupt(PIT_1);

			GPIO_clear_pin(GPIO_C,bit_5);
		}
		else
		{
			/* shut down buzzer */
			GPIO_clear_pin(GPIO_C,bit_5);
		}
	}
}

uint8_t get_time_g()
{
	return time_g;
}

void reset_game_timeout()
{
	seconds_g = 0;
	time_g = 0;
	timeout_status_flag = FALSE;
}
