/*
	\file 	  terminal.c
	\brief	  This is the source file that contains the functions that display information by UART.

	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez, ie705694

	\date	  03/05/2019

	center coordinates 25,10
*/

#include "terminal.h"

void terminal_menu_start(void)
{
	LCD_terminal_startup();
}

void terminal_menu_select0(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0);
	LCD_nokia_send_string("MENU");
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string("------------");
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string("1)Classic");
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string("2)Pitch");
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string("3)Tuner");
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string("4)Scores");
}

void terminal_menu_select1(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0);
	LCD_nokia_send_string("MENU");
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string("------------");
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string(" 1)Classic");
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string("2)Pitch");
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string("3)Tuner");
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string("4)Scores");
}

void terminal_menu_select2(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0);
	LCD_nokia_send_string("MENU");
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string("------------");
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string("1)Classic");
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string(" 2)Pitch");
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string("3)Tuner");
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string("4)Scores");
}

void terminal_menu_select3(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0);
	LCD_nokia_send_string("MENU");
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string("------------");
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string("1)Classic");
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string("2)Pitch");
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string(" 3)Tuner");
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string("4)Scores");
}

void terminal_menu_select4(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0);
	LCD_nokia_send_string("MENU");
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string("------------");
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string("1)Classic");
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string("2)Pitch");
	LCD_nokia_goto_xy(0,4);
	LCD_nokia_send_string("3)Tuner");
	LCD_nokia_goto_xy(0,5);
	LCD_nokia_send_string(" 4)Scores");
}

void terminal_menu_op1(void)
{
	LCD_nokia_clear();
	LCD_set_frame();
	LCD_nokia_goto_xy(15,10);
	LCD_nokia_send_string("Classic");
	LCD_nokia_goto_xy(25,11);
	LCD_nokia_send_string("Mode");
}

void terminal_menu_op2(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(22,10);
	LCD_nokia_send_string("Simon");
	LCD_nokia_goto_xy(25,11);
	LCD_nokia_send_string("Says");
}

void terminal_menu_op3(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(22,10);
	LCD_nokia_send_string("Guitar");
	LCD_nokia_goto_xy(25,11);
	LCD_nokia_send_string("Tuner");
}

void terminal_menu_op4(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("Leaderboard");
}


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
