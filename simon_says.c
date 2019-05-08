/*
 * simon_says.c
 *
 *  Created on: May 7, 2019
 *      Author: LuisFernando
 */
#include "simon_says.h"

//#define DEBUG

uint8_t buffer_sequence[SIMON_SEQUENCE] = {0};
boolean_t sequence_complete;
static uint8_t current_key;
static uint8_t prev_key;
boolean_t key_flag;

sequence_map_t sequence_map[SEQUENCE_SIZE] =
{
	{SEQUENCE_ZERO,		{DO,RE,MI,SOL,LA}},
	{SEQUENCE_ONE,		{RE,SOL,LA,DO,DO}},
	{SEQUENCE_TWO,		{DO,MI,SOL,LA,RE}},
	{SEQUENCE_THREE,	{SOL,MI,LA,DO,RE}},
	{SEQUENCE_FOUR,		{LA,SOL,MI,RE,DO}},
	{SEQUENCE_FIVE,		{MI,SOL,DO,RE,LA}},
	{SEQUENCE_SIX,		{DO,SOL,MI,RE,RE}},
	{SEQUENCE_SEVEN,	{RE,DO,SOL,DO,MI}},
};


static FSM_SS_t FSM_Buffer[5]=
{
	{&buffer_sequence[0],   {buffer_S2,  buffer_S3, buffer_S4, buffer_S5, buffer_S1}},
	{&buffer_sequence[1],   {buffer_S3,  buffer_S4, buffer_S5, buffer_S1, buffer_S2}},
	{&buffer_sequence[2],   {buffer_S4,  buffer_S5, buffer_S1, buffer_S2, buffer_S3}},
	{&buffer_sequence[3],   {buffer_S5,  buffer_S1, buffer_S2, buffer_S3, buffer_S4}},
	{&buffer_sequence[4],   {buffer_S1,  buffer_S2, buffer_S3, buffer_S4, buffer_S5}},
};

void generate_sequence_buffer(void)
{
	uint8_t rand_number = 0;
	sequence_complete = FALSE;
	rand_number = FTM_get_counter_reg();
	printf("Sequence: %d\n",rand_number);
	get_sequence(rand_number);
	/*Enable interrupts*/
	PIT_enable_interrupt(PIT_0);
	PIT_enable_interrupt(PIT_1);
}

void get_sequence(uint8_t rand_number_t)
{
	uint8_t i = 0;

	for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
	{
		/*sequence*/
		buffer_sequence[i] = sequence_map[rand_number_t].simon_says_sequence[i];
		/*PRINT FOR DEBUG*/
		printf("%d\n",buffer_sequence[i]);
	}
}

void send_sequence_buzzer(void)
{
	static uint8_t index = 0;
	if(TRUE == PIT_get_interrupt_flag_status(PIT_0))
	{
		note_frequency(buffer_sequence[index]);
		index++;
		if(index >= SIMON_SEQUENCE)
		{
			index = 0;
			/*Disable interrupt of the pits*/
			PIT_disable_interrupt(PIT_0);
			PIT_disable_interrupt(PIT_1);
			GPIO_clear_pin(GPIO_C,bit_5);
			SS_handle_user_input();
		}
		GPIO_clear_pin(GPIO_C,bit_5);
	}
}

void SS_handle_user_input(void)
{
	uint8_t key_number, current_key, i;
	boolean_t correct_flag;
	NoteBuffer_t current_state;

	correct_flag = FALSE;
	current_state = buffer_S1;
	i = 0;

	do
	{
		if(prev_key == current_key)
		{
			FREQ_voltage_drop();
		}
		else
		{
			prev_key = current_key;
		}
		i++;
		printf("Play note #%i\n", i);
		key_flag = FREQ_get_current_note(*FSM_Buffer[current_state].key_number);
		if(key_flag)
		{
			printf("Correct!\n");
			current_state = FSM_Buffer[current_state].next[0];
			correct_flag = TRUE;
		}
		else
		{
			correct_flag = FALSE;
			current_state = buffer_S1;
		}
	}while(buffer_S1 != current_state);


	if(TRUE == correct_flag)
	{
		printf("YOU WON!\n");
	}
	else
	{
		printf("GAME OVER\n");
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
