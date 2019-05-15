/*
	\file 	  terminal.c
	\brief	  This is the source file that contains the functions that display information by UART.

	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694

	\date	  03/05/2019

	center coordinates 25,10
*/

#include "terminal.h"

void terminal_menu_start(void)
{
	LCD_terminal_startup();
	terminal_press_start_msg();
}

void terminal_menu_select0(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(25,0);
	LCD_nokia_send_string("MENU");
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string("------------");
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string("1)Classic ");
	LCD_nokia_goto_xy(0,3);
	LCD_nokia_send_string("2)Scores");
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
	LCD_nokia_send_string("2)Scores");
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
	LCD_nokia_send_string(" 2)Scores");
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
	LCD_set_frame();
	LCD_nokia_goto_xy(22,10);
	LCD_nokia_send_string("Records");
}

void terminal_playnote1(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("Play Note #1");
}

void terminal_playnote2(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("Play Note #2");
}

void terminal_playnote3(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("Play Note #3");
}

void terminal_playnote4(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("Play Note #4");
}

void terminal_playnote5(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("Play Note #5");
}

void terminal_victory_msg(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("YOU WON!");
}

void terminal_game_over_msg(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("GAME OVER");
}

void terminal_correct_msg(void)
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,10);
	LCD_nokia_send_string("Correct!");
}

void terminal_press_start_msg(void)
{
	LCD_nokia_goto_xy(5,45);
	LCD_nokia_send_string("Press start");
}

void terminal_enter_your_initials()
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(0,1);
	LCD_nokia_send_string("Enter your");
	LCD_nokia_goto_xy(0,2);
	LCD_nokia_send_string("initials:");
}

void terminal_score_saved()
{
	LCD_nokia_clear();
	LCD_nokia_goto_xy(18,10);
	LCD_nokia_send_string("score");
	LCD_nokia_goto_xy(18,11);
	LCD_nokia_send_string("saved");
}
