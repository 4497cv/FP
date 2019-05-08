/*
 * frequency_decoder.h
 *
 *  Created on: 2 may. 2019
 *      Author: César
 */

#ifndef FREQUENCY_DECODER_H_
#define FREQUENCY_DECODER_H_

#include "adc.h"
#include <stdio.h>

#define STRING_MAX 5

#define C1 1164
#define D1 1294
#define E1 1552
#define F1 1682
#define G1 1811
#define A1 2070
#define B1 2329
#define C2 2458

#define C1_1 1
#define C1_2 1
#define C1_3 6
#define C1_4 4

#define D1_1 1
#define D1_2 2
#define D1_3 9
#define D1_4 4

#define E1_1 1
#define E1_2 5
#define E1_3 5
#define E1_4 2

#define F1_1 1
#define F1_2 9
#define F1_3 4
#define F1_4 1

#define G1_1 1
#define G1_2 8
#define G1_3 1
#define G1_4 1

#define A1_1 2
#define A1_2 0
#define A1_3 7
#define A1_4 0

#define B1_1 2
#define B1_2 3
#define B1_3 2
#define B1_4 9

#define C2_1 2
#define C2_2 4
#define C2_3 5
#define C2_4 8

#define NSAMPLES 100
#define KEYMAP_SIZE 7

typedef struct
{
   uint8_t key;
   uint8_t centi;
   uint8_t milli;
   uint8_t micro;
   uint8_t nano;
} Keymap_t;

uint8_t FREQ_get_current_note(void);

uint8_t FREQ_decode_voltage(uint8_t voltage_string[STRING_MAX]);

void FREQ_show_current_voltage(uint8_t voltage_string[STRING_MAX]);

#endif /* FREQUENCY_DECODER_H_ */
