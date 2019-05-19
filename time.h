/**
	\file time.h
	\brief
		This is the header file for the time module.
		This library contains functions that are helpful for time operations,
		related with any real time clock hardware.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez,ie705694
	\date	  25/04/2019
 */

#ifndef TIME_H_
#define TIME_H_

#include "MK64F12.h"
#include "bits.h" 

#ifndef DEBUG
	/** Debug code **/
	#include <stdio.h>
#endif

#define ZERO        0
#define ONE         1
#define TWO         2
#define THREE       3
#define FOUR        4
#define FIVE        5
#define SIX         6
#define SEVEN       7
#define EIGHT       8
#define NINE        9
#define TEN         10
#define ELEVEN      11
#define TWELVE      12
#define THIRTEEN    13
#define FOURTEEN    14
#define FIFTHTEEN   15
#define SIXTEEN     16
#define SEVENTEEN   17
#define EIGHTEEN    18
#define NINETEEN    19
#define TWENTY      20
#define TWENTYONE   21
#define TWENTYTWO   22
#define TWENTYTHREE 23
#define TWENTYFOUR  24
#define TWENTYFIVE  25
#define TWENTYSIX   26
#define TWENTYSEVEN 27
#define TWENTYEIGHT 28
#define TWENTYNINE  29
#define THIRTY      30
#define THIRTYONE   31
#define THIRTYTWO   32
#define THIRTYTHREE 33
#define THIRTYFOUR  34
#define THIRTYFIVE  35
#define THIRTYSIX 	36
#define THIRTYSEVEN 37
#define THIRTYEIGHT 38
#define THIRTYNINE 	39
#define FOURTY      40
#define FOURTYONE   41
#define FOURTYTWO   42
#define FOURTYTHREE 43
#define FOURTYFOUR  44
#define FOURTYFIVE  45
#define FOURTYSIX   46
#define FOURTYSEVEN 47
#define FOURTYEIGHT 48
#define FOURTYNINE  49
#define FIFTY       50
#define FIFTYONE    51
#define FIFTYTWO    52
#define FIFTYTHREE  53
#define FIFTYFOUR   54
#define FIFTYFIVE   55
#define FIFTYSIX    56
#define FIFTYSEVEN  57
#define FIFTYEIGHT  58
#define FIFTYNINE   59

#define TABLE_SIZE  60
#define ASCII_CONV  48

#define RS_MASK     (0x0F)
#define BIT8_MASK   (0x10)

#define HOUR_CAP    0
#define MIN_CAP     1
#define SEC_CAP     2
#define DAY_CAP     3
#define MONTH_CAP   4
#define YEAR_CAP    5

typedef enum
{
	MENU,
	SETHOUR,
	SETDATE,
	READHOUR,
	READDATE,
	WRITEMEM,
	SHOWMEM,
	RETURN
}	Time_type;

typedef struct
{
	uint8_t nval;
   	uint8_t unit;
   	uint8_t decimal;
} 	Keymap_time_t;



uint8_t get_table_value(uint8_t unit, uint8_t decimal);

void get_table_value_dec2hex(uint8_t number);

uint8_t get_global_unit(void);

uint8_t get_global_decimal(void);
#endif /* TIME_H_ */
