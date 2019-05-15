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
#define TIME_LIMIT 30

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

void generate_sequence_buffer(void);

void get_sequence(uint8_t rand_number_t);
void set_initial_state();
void send_sequence_buzzer(void);

void play_sequence();

void SS_handle_user_input(void);
void victory_buzzer(void);
void handle_time_interrupt(void);
uint8_t SS_note_convert_to_number(uint8_t keynote);
void update_timeout_status_flag(void);
boolean_t get_buzzer_end_flag_status(void);
void victory_sound();

#endif /* SIMON_SAYS_H_ */
