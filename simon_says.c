/*
 * simon_says.c
 *
 *  Created on: May 7, 2019
 *      Author: LuisFernando
 */
#include "simon_says.h"

uint8_t rand_number = 0;


void get_rand_number(void)
{
	rand_number = FTM0->CNT;
}
