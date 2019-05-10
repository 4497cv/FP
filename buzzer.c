/*
	\file 	  buzzer.c
	\brief:
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  10/05/2019
*/

#include "buzzer.h"

const float freq_delay [7] =
{
	0.00383,	/*DO*/
	0.00341,	/*RE*/
	0.00303,	/*MI*/
	0.00286,	/*FA*/
	0.00255,	/*SOL*/
	0.00227,	/*LA*/
	0.00202		/*SI*/
};

void buzzer_update_freq(float delay)
{
	/*Set the delay for the pit_1*/
	PIT_delay(PIT_1, SYSTEM_CLOCK, delay);
}

void buzzer_toogle(void)
{
	GPIO_toogle_pin(GPIO_C,bit_5);
}

void note_frequency(uint8_t index)
{
	uint8_t i;

	switch(index)
	{
		case C:
			i = 0;
		break;
		case D:
			i = 1;
		break;
		case E:
			i = 2;
		break;
		case F:
			i = 3;
		break;
		case G:
			i = 4;
		break;
		case A:
			i = 5;
		break;
		case B:
			i = 6;
		break;
	}

	buzzer_update_freq(freq_delay[i]);
}
