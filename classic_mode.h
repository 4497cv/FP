/*
	\file 	  classic_mode.h
	\brief	  This header file contains the declaration of the functions used in the frequency guessing game. 
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  03/05/2019
*/

#ifndef CLASSIC_MODE_H_
#define CLASSIC_MODE_H_

#include <flextimer.h>
#include "bits.h"
#include "gpio.h"
#include "pit.h"
#include "LM2907.h"
#include "terminal.h"

#define SEQUENCE_SIZE  8
#define BUFFER_SIZE    5
#define TIME_LIMIT     15

typedef enum{DO,RE,MI,FA,SOL,LA,SI} string_note_t;

typedef struct
{
	uint8_t *key_number;
	NoteBuffer_t next[BUFFER_SIZE];
} FSM_SS_t;

typedef struct
{
	void(*fptr)(void);	//Text string
	NoteBuffer_t next[BUFFER_SIZE]; //FSM terminal states
} TERM_playnotes_t;

typedef struct
{
	uint8_t seq_index;
	musical_notes sequence_buffer[BUFFER_SIZE];
}sequence_map_t;

/*!
	@brief  This functions generates a random number, and selects a specific sequence of notes.
	@param[in] void
	@return	  void
 */
void CM_generate_sequence_buffer(void);

/*!
	@brief     This function updates the global sequence buffer with the specific sequence of notes.
	@param[in] void
	@return	   void
 */
void CM_get_sequence(uint8_t rand_number_t);

/*!
	@brief     This function handles the game's time; handles timeout and verifies if the user has won or lost.
	@param[in] void
	@return	   void
 */
void CM_handle_time_interrupt(void);

/*!
	@brief     This function verifies if the current seconds count has reached its specified limit.
			   Indicates if a timeout has occurred.
	@param[in] void
	@return	   void
 */
void CM_update_timeout_status(void);

/*!
	@brief     This function returns the current in total global time value.
	@param[in] void
	@return	   uint8_t
 */
uint8_t CM_get_time_g(void);

/*!
	@brief     This function resets the game's register initial values.
	@param[in] void
	@return	   void
 */
void CM_reset_game(void);

/*!
	@brief     This function increases the current seconds and the total time.
	@param[in] void
	@return	   void
 */
void CM_increase_time(void);

#endif
