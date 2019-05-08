/*
 * simon_says.c
 *
 *  Created on: May 7, 2019
 *      Author: LuisFernando
 */
#include "simon_says.h"

//#define DEBUG

uint8_t buffer_sequence[SIMON_SEQUENCE] = {0};

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

void get_rand_number(void)
{
	uint8_t rand_number = 0;
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
		}
		GPIO_clear_pin(GPIO_C,bit_5);
	}
}
