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
#include "spi.h"
#include "LCD_nokia_images.h"


#define TERM_NUM_ST     6
#define SCREEN_LIMIT    84
#define INDEX_INIT 		0
#define FSM_START_SIZE  6
#define FSM_SELECT_SIZE 9
#define FSM_OP1_SIZE    7
#define FSM_OP2_SIZE    7
#define FSM_TOTAL_STATES  10

typedef struct
{
	void(*fptr)(void);	//Text string
	terminal_state_t next[TERM_NUM_ST]; //FSM terminal states
} FSM_terminal_t;

void terminal_menu_start(void);

void terminal_menu_select0(void);
void terminal_menu_select1(void);
void terminal_menu_select2(void);
void terminal_menu_select3(void);
void terminal_menu_select4(void);

void terminal_menu_op1(void);
void terminal_menu_op2(void);
void terminal_menu_op3(void);
void terminal_menu_op4(void);

#endif /* UART_TERM_H_ */
