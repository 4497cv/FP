/*
 * main.c
 *
 *  Created on: 2 may. 2019
 *      Author: César
 */

#include "system.h"
#include "frequency_decoder.h"
#include "guitar_tuner.h"

int main(void)
{
	system_init();

	while(1)
	{
		notedetector();
	}

	return 0;
}
