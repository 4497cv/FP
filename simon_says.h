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

typedef struct
{
	uint8_t seq_index;
	uint8_t simon_says_sequence[SIMON_SEQUENCE];
}sequence_map_t;

void get_rand_number(void);

void get_sequence(void);

#endif /* SIMON_SAYS_H_ */
