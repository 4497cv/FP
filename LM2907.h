/*
	\file 	  LM2907.h
	\brief	  This header file contains functions the frequency to voltage converter module.
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  03/05/2019
*/

#ifndef FREQUENCY_DECODER_H_
#define FREQUENCY_DECODER_H_

#include "adc.h"
#include "classic_mode.h"

/* DO voltage: 414.1 mV*/
#define C1_1 4
#define C1_2 1
#define C1_3 4
#define C1_4 1
/*~~~~~~~~~~~~~~~~~~~~~*/
/* RE voltage: 465.7 mV*/
#define D1_1 4
#define D1_2 6
#define D1_3 5
#define D1_4 7
/*~~~~~~~~~~~~~~~~~~~~~*/
/* MI voltage: 517.6 mV*/
#define E1_1 5
#define E1_2 1
#define E1_3 7
#define E1_4 6
/*~~~~~~~~~~~~~~~~~~~~~*/
/* FA voltage: 582.3 mV*/
#define F1_1 5
#define F1_2 8
#define F1_3 2
#define F1_4 3
/*~~~~~~~~~~~~~~~~~~~~~*/
/* SOL voltage: 621.1 mV*/
#define G1_1 6
#define G1_2 2
#define G1_3 1
#define G1_4 1
/*~~~~~~~~~~~~~~~~~~~~~*/
/* LA voltage: 685.8 mV*/
#define A1_1 6
#define A1_2 8
#define A1_3 5
#define A1_4 8
/*~~~~~~~~~~~~~~~~~~~~~*/
/* SI voltage: 815.2 mV*/
#define B1_1 8
#define B1_2 1
#define B1_3 5
#define B1_4 2
/*~~~~~~~~~~~~~~~~~~~~~*/

#define STRING_MAX 5
#define KEYMAP_SIZE 7
#define NSHIFT 8
#define DECIMAL_SHIFT 10

typedef struct
{
   uint8_t key;
   uint8_t centi;
   uint8_t milli;
   uint8_t micro;
   uint8_t nano;
} Keymap_t;

/*!
	@brief     This function reads the current value from the analog to digital converter, and associates the 
              voltage value to a certain musical note.
	@param[in] void
	@return	  void
 */
void LM2907_get_current_note(void);

/*!
	@brief     This function verifies and associates a given voltage to an specific musical note.
	@param[in] uint8_t, uint8_t, uint8_t
	@return	   uint8_t
 */
uint8_t LM2907_decode_voltage(uint8_t voltage_string1, uint8_t voltage_string2,uint8_t voltage_string3);

/*!
	@brief     This function verifies if the note played corresponds to the current buffer note, and updates the
			   global flag that indicates that a note has been found.
	@param[in] uint8_t
	@return	   void
 */
void LM2907_update_note_found_flag_status(uint8_t key);

/*!
	@brief     This function gets the current state of the global flag that is used to indicate that a note has been found.
	@param[in] void
	@return	   boolean_t
 */
boolean_t LM2907_get_note_found_flag(void);

/*!
	@brief     This function updates the current global register that sets the current value of the note.
	@param[in] uint8_t
	@return	   void
 */
void LM2907_update_current_note(uint8_t note);

/*!
	@brief     This function prints the current character in terminal, used only for debugging purposes.
	@param[in] uint8_t
	@return	   void
 */
void LM2907_show_current_key(uint8_t key);

/*!
	@brief     This function prints the current voltage value read by the ADC, used only for debugging purposes.
	@param[in] uint8_t
	@return	   void
 */
void LM2907_show_current_voltage(uint8_t voltage_string[STRING_MAX]);

#endif /* FREQUENCY_DECODER_H_ */
