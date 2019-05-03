/*
 * uart_tera.h
 *
 *  Created on: Apr 10, 2019
 *      Author: LuisFernando
 */

#ifndef TERM_H_
#define TERM_H_

#include "bits.h"
#include "uart.h"

#define TERM_NUM_ST 4

typedef enum
{
	terminal_start,
	terminal_menu,
	terminal_op1,
	terminal_op2
} terminal_state_t;

typedef struct
{
	void(*fptr)(void);
	terminal_state_t next[4];
} FSM_terminal_t;

typedef enum
{
	ASCII_ENTER = 13,
	ASCII_ESC = 27,
	/**/
	ASCII_LETTER_A = 65,
	ASCII_LETTER_B = 66,
	ASCII_LETTER_C = 67,
	ASCII_LETTER_D = 68,
	ASCII_LETTER_E = 69,
	ASCII_LETTER_F = 70,
	ASCII_LETTER_a = 97,
	ASCII_LETTER_b = 98,
	ASCII_LETTER_c = 99,
	ASCII_LETTER_d = 100,
	ASCII_LETTER_e = 101,
	ASCII_LETTER_f = 102,
	/**/
	ASCII_ONE = 49,
	ASCII_TWO = 50,
	ASCII_THREE = 51,
	ASCII_FOUR = 52,
	ASCII_FIVE = 53,
	ASCII_SIX = 54,
	ASCII_SEVEN = 55,
	ASCII_EIGHT = 56,
	ASCII_NINE = 57,
	ASCII_ZERO = 48,
	/**/
	ASCII_TIME_FORM = 58,
	ASCII_DATE_FORM = 47,
	ASCII_STOP = 59,
	ASCII_DOT = 250
}ASCII_type;

void terminal_menu_start(void);

void terminal_menu_select(void);

void terminal_menu_op1(void);

void terminal_menu_op2(void);

#endif /* UART_TERM_H_ */
