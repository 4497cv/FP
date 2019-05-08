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
	{SEQUENCE_ZERO,		{DO,DO,RE,SI,LA,SOL}},
	{SEQUENCE_ONE,		{RE,SI,DO,LA,SOL,FA}},
	{SEQUENCE_TWO,		{DO,RE,DO,LA,MI,SOL}},
	{SEQUENCE_THREE,	{SOL,LA,MI,RE,DO,RE}},
	{SEQUENCE_FOUR,		{SI,SI,SOL,DO,FA,LA}},
	{SEQUENCE_FIVE,		{FA,FA,SI,SI,LA,SOL}},
	{SEQUENCE_SIX,		{MI,RE,DO,SOL,SI,LA}},
	{SEQUENCE_SEVEN,	{SOL,DO,FA,SI,LA,LA}},
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
