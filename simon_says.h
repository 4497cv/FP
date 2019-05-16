/*
 * simon_says.h
 *
 *  Created on: May 7, 2019
 *      Author: LuisFernando
 */

#ifndef SIMON_SAYS_H_
#define SIMON_SAYS_H_

#include "bits.h"
#include "gpio.h"
#include "FlexTimer.h"
#include "pit.h"
#include "buzzer.h"
#include "frequency_decoder.h"
#include "stdio.h"
#include "terminal.h"

#define SEQUENCE_SIZE  8
#define SIMON_SEQUENCE 5
#define BUFFER_SIZE    6
#define BUFFER_LIMIT   5
#define TIME_LIMIT 5

typedef enum
{
	DO,
	RE,
	MI,
	FA,
	SOL,
	LA,
	SI
} string_note_t;


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
void generate_sequence_buffer(void);

/*\brief Funct to get a rand sequence using the FTM
 *\param[add] rand_number_t
 * */
void get_sequence(uint8_t rand_number_t);

/*\brief
 *\param[add] void
 * */
void set_initial_state(void);

/*\brief
 *\param[add] void
 * */
void send_sequence_buzzer(void);

/*\brief Funct to play the sequence to be played
 *\param[add] void
 * */
void play_sequence(void);

/*\brief
 *\param[add] void
 * */
void SS_handle_user_input(void);

/*\brief Funct to send a victory song or noise for the user
 *\param[add] void
 * */
void victory_buzzer(void);

/*\brief
 *\param[add] void
 * */
void handle_time_interrupt(void);

/*\brief
 *\param[add] keynote
 * */
uint8_t SS_note_convert_to_number(uint8_t keynote);

/*\brief
 *\param[add] void
 * */
void update_timeout_status_flag(void);

/*\brief
 *\param[add] void
 * */
boolean_t get_buzzer_end_flag_status(void);

/*\brief
 *\param[add] void
 * */
void victory_sound(void);

/*\brief
 *\param[add] void
 * */
uint8_t get_time_g(void);

/*\brief
 *\param[add] void
 * */
void reset_game_timeout(void);

#endif /* SIMON_SAYS_H_ */
