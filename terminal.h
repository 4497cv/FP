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
#include "lcd_nokia.h"
#include "LCD_nokia_images.h"
#include "eeprom.h"

#define TERM_NUM_ST     6U
#define SCREEN_LIMIT    84U
#define INDEX_INIT 		0U
#define FSM_START_SIZE  6U
#define FSM_SELECT_SIZE 9U
#define FSM_OP1_SIZE    7U
#define FSM_OP2_SIZE    7U
#define FSM_TOTAL_STATES  10U
#define SPI_OFFSET 8U
#define ASCII_DECODE 0x30U

typedef struct
{
	void(*fptr)(void);	//Text string
	terminal_state_t next[TERM_NUM_ST]; //FSM terminal states
} FSM_terminal_t;

typedef struct
{
	uint8_t x;
	uint8_t y;
	uint8_t *str;
	void(*Fptr)(void);	//Text string
} FSM_terminal_select_t;


/*\brief Funct to display the menu in the spi
 *\param[add] void
 * */
void terminal_menu_start(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_select0(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_select1(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_select2(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_select3(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_select4(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_op1(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_op2(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_op3(void);

/*\brief Funct to make the user see wich option they are choosing
 *\param[add] void
 * */
void terminal_menu_op4(void);

/*\brief Funct to make the user see wich note they need to play
 *\param[add] void
 * */
void terminal_playnote1(void);

/*\brief Funct to make the user see wich note they need to play
 *\param[add] void
 * */
void terminal_playnote2(void);

/*\brief Funct to make the user see wich note they need to play
 *\param[add] void
 * */
void terminal_playnote3(void);

/*\brief Funct to make the user see wich note they need to play
 *\param[add] void
 * */
void terminal_playnote4(void);

/*\brief Funct to make the user see wich note they need to play
 *\param[add] void
 * */
void terminal_playnote5(void);

/*\brief Funct to read if there was any drop to avoid reading multiple time the same note
 *\param[add] void
 * */
void terminal_VoltageDrop(void);

/*\brief Funct to make the user see that he won
 *\param[add] void
 * */
void terminal_victory_msg(void);

/*\brief Funct to make the user see that he lost
 *\param[add] void
 * */
void terminal_game_over_msg(void);

/*\brief
 *\param[add] void
 * */
void terminal_correct_msg(void);

/*\brief
 *\param[add] void
 * */
void terminal_press_start_msg(void);

/*\brief Funct to make the user see that he need to put an username, just as an arcade game
 *\param[add] void
 * */
void terminal_enter_your_initials(void);

/*\brief Funct to make sure the score was saved correctly
 *\param[add] void
 * */
void terminal_score_saved(void);

/*\brief Funct to make the user see his score
 *\param[add] void
 * */
void terminal_user_score(void);

#endif /* UART_TERM_H_ */
