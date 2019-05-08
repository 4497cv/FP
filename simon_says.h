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

#define SEQUENCE_SIZE 8
#define SIMON_SEQUENCE 5

typedef enum
{
	SEQUENCE_ZERO,
	SEQUENCE_ONE,
	SEQUENCE_TWO,
	SEQUENCE_THREE,
	SEQUENCE_FOUR,
	SEQUENCE_FIVE,
	SEQUENCE_SIX,
	SEQUENCE_SEVEN
}sequence_enum_t;

typedef enum
{
	DO,
	RE,
	MI,
	FA,
	SOL,
	LA,
	SI
}string_note_t;

typedef enum
{
	buffer_S1,
	buffer_S2,
	buffer_S3,
	buffer_S4,
	buffer_S5,
	buffer_S6,
	buffer_S7,
	buffer_S8,
	buffer_S9
} NoteBuffer_t;

typedef struct
{
	uint8_t *key_number;
	NoteBuffer_t next[5];
} FSM_SS_t;

typedef struct
{
	uint8_t seq_index;
	uint8_t simon_says_sequence[SIMON_SEQUENCE];
}sequence_map_t;

void generate_sequence_buffer(void);

void get_sequence(uint8_t rand_number_t);

void send_sequence_buzzer(void);
void SS_handle_user_input(void);
uint8_t SS_note_convert_to_number(uint8_t keynote);

#endif /* SIMON_SAYS_H_ */
