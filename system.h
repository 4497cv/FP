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

#include <flextimer.h>
#include "MK64F12.h"
#include "terminal.h"
#include "nvic.h"
#include "gpio.h"
#include "lcd_nokia.h"
#include "spi.h"
#include "i2c.h"
#include "eeprom.h"
#include "LM2907.h"
#include "classic_mode.h"

#define SYSTEM_CLOCK (21000000U)
#define BPS_RATE (1.0F)
#define SAMPLING_RATE (0.1F)
#define EEPROM_USER_ADDRESS_ONE   0x00U
#define EEPROM_USER_ADDRESS_TWO   0x06U
#define EEPROM_USER_ADDRESS_THREE 0x12U

#define SYS_NUM_ST 6
#define SYSTEM_STATES 3
#define ID_SIZE 3

typedef struct
{
	void(*fptr)(void);
	system_state_t next[2];
} FSM_system_t;

typedef enum
{
	FIRST_LETTER,
	SECOND_LETTER,
	THIRD_LETTER,
	SCORE_SAVED
} letter_t;

/*\brief All system initialitation
 *\param[add] void
 * */
void system_init(void);

/*\brief Funct for the menu of the system
 *\param[add] void
 * */
void system_menu(void);

/*\brief SPI funct for the classic mode (GAME MODE)
 *\param[add] void
 * */
void system_play_classic(void);

/*\brief
 *\param[add] void
 * */
void system_play_SimonMode(void);

/*\brief
 *\param[add] void
 * */
void system_guitar_tuner(void);

/*\brief
 *\param[add] void
 * */
void system_dynamic_select_handler(void);

/*\brief
 *\param[add] void
 * */
boolean_t get_menu_select_flag(uint8_t mailbox_value);

/*\brief
 *\param[add] void
 * */
boolean_t valid_menu_select(uint8_t mailbox_value);

/*\brief
 *\param[add] void
 * */
void system_fsm_handler(void);

/*\brief Func to access the scores in the SPI
 *\param[add] void
 * */
void system_player_board(void);

/*\brief Funct used to select the next operation that the state machin will need to point
 *\param[add] void
 * */
void system_select_next_op(void);

/*\brief Funct that gets the ISR for the interruption for access a certain funct
 *\param[add] void
 * */
void system_set_start(void);

/*\brief Funct that will set the pointer to the functs needed to store the score in the eeprom
 *\param[add] void
 * */
void system_user_record_capture(uint8_t time_g);

/*\brief Funct to go back to the main menu
 *\param[add] void
 * */
void reset_menu(void);

#endif /* SYSTEM_H_ */
