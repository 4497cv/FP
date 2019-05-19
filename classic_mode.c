/*
	\file 	  classic_mode.c
	\brief	  This source file contains the implementation for the frequency guessing game. 
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  03/05/2019
*/

#include "classic_mode.h"

static uint8_t buffer_sequence[BUFFER_SIZE] = {0};
static boolean_t sequence_complete_g;
static uint8_t sequence_number;
static boolean_t timeout_status_flag = FALSE;
static NoteBuffer_t current_state = buffer_S1;
static volatile uint8_t seconds_g = 0;
static volatile uint8_t time_g = 0;

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

static FSM_SS_t FSM_Buffer[BUFFER_SIZE]=
{
	{&buffer_sequence[0],   {buffer_S2,  buffer_S3, buffer_S4, buffer_S5, buffer_S1}},
	{&buffer_sequence[1],   {buffer_S3,  buffer_S4, buffer_S5, buffer_S1, buffer_S2}},
	{&buffer_sequence[2],   {buffer_S4,  buffer_S5, buffer_S1, buffer_S2, buffer_S3}},
	{&buffer_sequence[3],   {buffer_S5,  buffer_S1, buffer_S2, buffer_S3, buffer_S4}},
	{&buffer_sequence[4],   {buffer_S1,  buffer_S2, buffer_S3, buffer_S4, buffer_S5}}
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
		current_state = FSM_Buffer[current_state].next[0];
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
		CM_increase_time();
		/* Handle time out and increase time */
		CM_update_timeout_status();
	}
}

void CM_update_timeout_status(void)
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

uint8_t CM_get_time_g(void)
{
	/* return in total time count */
	return time_g;
}

void CM_reset_game_timeout(void)
{
	/* restart seconds count */
	seconds_g = ZERO;
	/* restart in total time count */
	time_g = ZERO;
	/* restart timeout flag */
	timeout_status_flag = FALSE;
}

void CM_increase_time(void)
{
	/* total seconds */
	time_g++;
	/* increment sequence state seconds */
	seconds_g++;
}
