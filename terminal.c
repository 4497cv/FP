/*
	\file 	  terminal.c
	\brief	  This is the source file that contains the functions that display information by UART.

	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez, ie705694

	\date	  03/05/2019
*/

#include "terminal.h"

void terminal_menu_start(void)
{
	LCD_terminal_startup();
}

void terminal_menu_select(void)
{
//	terminal_config_state_t current_state;
//
//	current_state = terminal_S0; //set initial state
//
//	FSM_terminal_config_t FSM_terminal_menu[FSM_SELECT_SIZE]=
//	{
//		{"\033[2J", 				 {terminal_S1, terminal_S2, terminal_S3, terminal_S4, terminal_S5, terminal_S6, terminal_S7, terminal_S8, terminal_S0}},
//		{"\033[0;30;41m", 			 {terminal_S2, terminal_S3, terminal_S4, terminal_S5, terminal_S6, terminal_S7, terminal_S8, terminal_S0, terminal_S1}},
//		{"\033[2J", 	  			 {terminal_S3, terminal_S4, terminal_S5, terminal_S6, terminal_S7, terminal_S8, terminal_S0, terminal_S1, terminal_S2}},
//		{"\033[0;47;40m",   		 {terminal_S4, terminal_S5, terminal_S6, terminal_S7, terminal_S8, terminal_S0, terminal_S1, terminal_S2, terminal_S3}},
//		{"\033[10;10H" ,			 {terminal_S5, terminal_S6, terminal_S7, terminal_S8, terminal_S0, terminal_S1, terminal_S2, terminal_S3, terminal_S4}},
//		{"1) Play classic mode\r",   {terminal_S6, terminal_S7, terminal_S8, terminal_S0, terminal_S1, terminal_S2, terminal_S3, terminal_S4, terminal_S5}},
//		{"\033[11;10H",   			 {terminal_S7, terminal_S8, terminal_S0, terminal_S1, terminal_S2, terminal_S3, terminal_S4, terminal_S5, terminal_S6}},
//		{"2) Guitar tuner \r", 	     {terminal_S8, terminal_S0, terminal_S1, terminal_S2, terminal_S3, terminal_S4, terminal_S5, terminal_S6, terminal_S7}},
//		{"\033[14;10H",  			 {terminal_S0, terminal_S1, terminal_S2, terminal_S3, terminal_S4, terminal_S5, terminal_S6, terminal_S7, terminal_S8}}
//	};
//
//	do
//	{
//		/* Send to terminal the state's current text */
//		UART_put_string(UART_0, FSM_terminal_menu[current_state].setup_txt);
//		/* get next state */
//		current_state = FSM_terminal_menu[current_state].next[INDEX_INIT];
//	}while(terminal_S0 != current_state); //repeat while all the states are completed
}

void terminal_menu_op1(void)
{

}

void terminal_menu_op2(void)
{

}
