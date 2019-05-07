/*
 * simon_says.c
 *
 *  Created on: May 7, 2019
 *      Author: LuisFernando
 */
#include "simon_says.h"

//#define DEBUG

uint8_t rand_number = 0;

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
	rand_number = FTM0->CNT;
	printf("%d\n",rand_number);
	get_sequence();
}

void get_sequence(void)
{
	uint8_t i = 0;
	uint8_t buffer_sequence[SIMON_SEQUENCE] = {0};
	switch(rand_number)
	{
	case SEQUENCE_ZERO:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_ZERO].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	case SEQUENCE_ONE:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_ONE].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	case SEQUENCE_TWO:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_TWO].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	case SEQUENCE_THREE:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_THREE].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	case SEQUENCE_FOUR:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_FOUR].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	case SEQUENCE_FIVE:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_FIVE].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	case SEQUENCE_SIX:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_SIX].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	case SEQUENCE_SEVEN:
		for(i = 0; i < SIMON_SEQUENCE + 1 ;i++)
		{
			buffer_sequence[i] = sequence_map[SEQUENCE_SEVEN].simon_says_sequence[i];

			printf("%d\n",buffer_sequence[i]);

		}
		break;
	default:
		break;
	}
}
