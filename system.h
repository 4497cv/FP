/*
	\file 	  system.h
	\brief	  This program contains the functions that configure the MCU's peripherals and external hardware.
			  It also contains the user menu.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez, ie705694
	\date	  02/05/2019
*/

#ifndef SYSTEM_H_
#define SYSTEM_H_

#include "terminal.h"
#include "uart.h"


typedef enum
{
	system_op1,
	system_op2
} system_state_t;

typedef struct
{
	void(*fptr)(void);
	system_state_t next[4];
} FSM_system_t;


void system_menu(void);

void system_play_classic(void);

void system_guitar_tuner(void);

#endif /* SYSTEM_H_ */
