/*
 * main.c
 *
 *  Created on: 2 may. 2019
 *      Author: César
 */

#include "system.h"

int main(void)
{
	system_init();

	while(1)
	{
		system_menu();
	}

	return 0;
}
