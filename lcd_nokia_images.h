

#ifndef LCD_NOKIA_IMAGES_H_
#define LCD_NOKIA_IMAGES_H_

#include "stdint.h"
#include "lcd_nokia.h"
#include "bits.h"
#include "terminal.h"
#include "system.h"
#include "pit.h"

#define FSM_LCD_STATES 13

typedef struct
{
	uint8_t *bitmap; //Text string
	states_t next[FSM_LCD_STATES]; //FSM terminal states
} FSM_LCD_t;

void LCD_terminal_startup(void);

void LCD_set_frame(void);

void LCD_set_pentagram_sequence(sequence_enum_t sequence_state, NoteBuffer_t note_state);

#endif /* LCD_NOKIA_IMAGES_H_ */

//{&logo_0[0], 		{terminal_S1, terminal_S2, terminal_S3, terminal_S4, terminal_S5, terminal_S0}},
//{&logo_0[0], 		{terminal_S2, terminal_S3, terminal_S4, terminal_S5, terminal_S0, terminal_S1}},
//{&logo_0[0], 		{terminal_S3, terminal_S4, terminal_S5, terminal_S0, terminal_S1, terminal_S2}},
//{&logo_0[0],  		{terminal_S4, terminal_S5, terminal_S0, terminal_S1, terminal_S2, terminal_S3}},
//{&logo_0[0],		{terminal_S5, terminal_S0, terminal_S1, terminal_S2, terminal_S3, terminal_S4}},
//{&logo_0[0],   	    {terminal_S0, terminal_S1, terminal_S2, terminal_S3, terminal_S4, terminal_S5}}
