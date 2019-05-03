/*
	\file 	  system.c
	\brief	  This program contains the functions that configure the MCU's peripherals and external hardware.
			  It also contains the user menu.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez, ie705694
	\date	  02/05/2019
*/

#include "system.h"

static terminal_state_t current_term_st; //current terminal state

FSM_terminal_t FSM_terminal[4]=
{
	{terminal_menu_start,     {terminal_menu,    terminal_op1,     terminal_op2, terminal_start}},
	{terminal_menu_select,    {terminal_op1,     terminal_op2,   terminal_start,  terminal_menu}},
	{terminal_menu_op1,       {terminal_op2,   terminal_start,    terminal_menu,   terminal_op1}},
	{terminal_menu_op2,       {terminal_start,  terminal_menu,     terminal_op1,   terminal_op2}}
};

FSM_system_t FSM_system[2]=
{
	{system_play_classic,    {system_op2,	 system_op1}},
	{system_guitar_tuner,    {system_op1,     system_op2}}
};

void system_menu(void)
{
	current_term_st = terminal_start; //set initial terminal state (display menu)
	FSM_terminal[current_term_st].fptr(); //invoke state's related function

	current_term_st = FSM_terminal[current_term_st].next[0]; //set initial terminal state (display menu)
	FSM_terminal[current_term_st].fptr(); //invoke state's related function






}



