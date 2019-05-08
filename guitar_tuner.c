/*
 * guitar_tuner.c
 *
 *  Created on: 7 may. 2019
 *      Author: César
 */

#include "guitar_tuner.h"

void guitar_tuner()
{
	uint8_t prev_key;
	uint8_t current_key;

	current_key = FREQ_get_current_note();

	if(prev_key != current_key)
	{
		printf("%c\n", current_key);
		prev_key = current_key;
	}

}
