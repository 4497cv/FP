/*
	\file 	  terminal.h
	\brief	  This is the header file that contains the functions that display information by UART.

	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez, ie705694

	\date	  03/05/2019
*/

#ifndef TERM_H_
#define TERM_H_

#include "bits.h"
#include "uart.h"

#define TERM_NUM_ST     4

#define INDEX_INIT 		0
#define FSM_START_SIZE  6
#define FSM_SELECT_SIZE 9
#define FSM_OP1_SIZE    7
#define FSM_OP2_SIZE    7
#define FSM_TOTAL_STATES  10
typedef struct
{
	int8_t *setup_txt; //Text string
	terminal_config_state_t next[FSM_TOTAL_STATES]; //FSM terminal states
} FSM_terminal_config_t;

typedef struct
{
	void(*fptr)(void);	//Text string
	terminal_state_t next[TERM_NUM_ST]; //FSM terminal states
} FSM_terminal_t;

void terminal_menu_start(void);

void terminal_menu_select(void);

void terminal_menu_op1(void);

void terminal_menu_op2(void);

#endif /* UART_TERM_H_ */
