/*
	\file 	  classic_mode.c
	\brief	  This source file contains the implementation for the frequency guessing game. 
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  03/05/2019
*/

#include "classic_mode.h"

static uint8_t buffer_sequence[BUFFER_SIZE];
static boolean_t sequence_complete_g;
static uint8_t sequence_number;
static boolean_t timeout_status_flag;
static NoteBuffer_t current_state;
static volatile uint8_t seconds_g;
static volatile uint8_t time_g;

static const sequence_map_t sequence_map[SEQUENCE_SIZE] =
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

static const FSM_SS_t FSM_Buffer[BUFFER_SIZE]=
{
	{&buffer_sequence[ZERO],   {buffer_S2,  buffer_S3, buffer_S4, buffer_S5, buffer_S1}},
	{&buffer_sequence[ONE],    {buffer_S3,  buffer_S4, buffer_S5, buffer_S1, buffer_S2}},
	{&buffer_sequence[TWO],    {buffer_S4,  buffer_S5, buffer_S1, buffer_S2, buffer_S3}},
	{&buffer_sequence[THREE],  {buffer_S5,  buffer_S1, buffer_S2, buffer_S3, buffer_S4}},
	{&buffer_sequence[FOUR],   {buffer_S1,  buffer_S2, buffer_S3, buffer_S4, buffer_S5}}
};

void CM_generate_sequence_buffer(void)
{
	/* get random sequence number (0-8)*/
    sequence_number = FTM_get_counter_reg();
    /* set that the sequence is not complete yet*/
	sequence_complete_g = FALSE;
	/* Update current global buffer */
	CM_get_sequence(sequence_number);
}

void CM_get_sequence(uint8_t sequence_index)
{
	uint8_t i;
	
	for(i = ZERO; BUFFER_SIZE > i ; i++)
	{
		/* update buffer sequence to global buffer */
		buffer_sequence[i] = sequence_map[sequence_index].sequence_buffer[i];
	}

	/* Displays on LCD screen corresponding note in music pentagram  */
	LCD_set_pentagram_sequence(sequence_number, buffer_S1);
}

void CM_handle_time_interrupt(void)
{
	boolean_t victory_flag; //this flag indicates if the user has won or lost the game
	boolean_t note_found_flag; //this flag indicates if a note has been found

	/* Sets current state corresponding buffer value to the frequency converter module */
	LM2907_update_current_note(*FSM_Buffer[current_state].key_number);

	/* get note found flag status */
	note_found_flag = LM2907_get_note_found_flag();

	if(note_found_flag)
	{
		/* send victory message to SPI */
		terminal_correct_msg();
		/* Displays on LCD screen corresponding note in music pentagram */
		LCD_set_pentagram_sequence(sequence_number, *FSM_Buffer[current_state].key_number);
		/* get game's next state status */
		current_state = FSM_Buffer[current_state].next[ZERO];
		/* reset seconds */
		seconds_g = ZERO;

		/* verify if the user has completed all the sequence */
		if(current_state == buffer_S1)
		{
			/* indicate that the user has won */
			victory_flag = TRUE;
		}
		else
		{
			/* indicate that the user has not won yet */
			victory_flag = FALSE;
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
		/* Disable PIT for adc sampling @ 2kHz */
		PIT_disable_interrupt(PIT_2);
		/* Disable PIT for time interrupt handler */
		PIT_disable_interrupt(PIT_3);
		/* Capture user initials */
		terminal_enter_your_initials();
		/* Store the user's time score */
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
		GPIO_set_playerboard_flag();
		terminal_enter_your_initials();
		system_user_record_capture(time_g);
	}
	else
	{
		/* increase current seconds and total time */
		CM_increase_time();
		/* Verify if a time out has ocurred */
		CM_update_timeout_status();
	}
}

void CM_update_timeout_status(void)
{
	/* Verify if the current seconds has reached the time limit */
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

uint8_t CM_get_time_g(void)
{
	/* return in total time count */
	return time_g;
}

void CM_reset_game(void)
{
	uint8_t i;

	/* restart seconds count */
	seconds_g = ZERO;
	/* restart in total time count */
	time_g = ZERO;
	/* restart timeout flag */
	timeout_status_flag = FALSE;
	/* Set initial state */
	current_state = buffer_S1;

	for(i = ZERO; BUFFER_SIZE > i; i++)
	{
		buffer_sequence[i] = ZERO;
	}
}

void CM_increase_time(void)
{
	/* total seconds */
	time_g++;
	/* increment sequence state seconds */
	seconds_g++;
}
