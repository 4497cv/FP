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
#define SIMON_SEQUENCE 5
#define BUFFER_SIZE    5
#define BUFFER_LIMIT   5
#define TIME_LIMIT 15

typedef enum{DO,RE,MI,FA,SOL,LA,SI} string_note_t;

typedef struct
{
	uint8_t *key_number;
	NoteBuffer_t next[5];
} FSM_SS_t;

typedef struct
{
	void(*fptr)(void);	//Text string
	NoteBuffer_t next[5]; //FSM terminal states
} TERM_playnotes_t;

typedef struct
{
	uint8_t seq_index;
	musical_notes sequence_buffer[SIMON_SEQUENCE];
}sequence_map_t;

/*\brief Funct that send to the buzzer the sequence so the player can hear it too
 *\param[add] void
 * */
void CM_generate_sequence_buffer(void);

/*\brief Funct to get a rand sequence using the FTM
 *\param[add] rand_number_t
 * */
void CM_get_sequence(uint8_t rand_number_t);

/*\brief
 *\param[add] void
 * */
void CM_handle_time_interrupt(void);

/*\brief
 *\param[add] void
 * */
void CM_update_timeout_status(void);

/*\brief
 *\param[add] void
 * */
uint8_t CM_get_time_g(void);
/*\brief
 *\param[add] void
 * */
void CM_reset_game_timeout(void);

void CM_increase_time(void);

#endif
