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

#include "MK64F12.h"
#include "terminal.h"
#include "nvic.h"
#include "gpio.h"
#include "lcd_nokia.h"
#include "spi.h"
#include "buzzer.h"
#include "FlexTimer.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (1.0F)

#define SYS_NUM_ST 6

typedef struct
{
	void(*fptr)(void);
	system_state_t next[2];
} FSM_system_t;


void system_init(void);

void system_menu(void);

void system_play_classic(void);

void system_play_SimonMode(void);

void system_guitar_tuner(void);

void system_dynamic_select_handler();

boolean_t get_menu_select_flag(uint8_t mailbox_value);

boolean_t valid_menu_select(uint8_t mailbox_value);

void system_fsm_handler(void);

void system_player_board();

void system_select_next_op();

void system_set_start();

#endif /* SYSTEM_H_ */
