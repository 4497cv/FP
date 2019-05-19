/**
	\file time.c
	\brief
		This is the source file for the time module.
		This library contains functions that are helpful for time operations,
		related with any real time clock (MCP7940N) hardware.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez,ie705694
	\date	  25/04/2019
 */

#include <time.h>

static Keymap_time_t global_time;

static const Keymap_time_t key_map[TABLE_SIZE]=
{
	{ZERO,        ZERO,  ZERO},
	{ONE,         ZERO,  ONE},
	{TWO,         ZERO,  TWO},
	{THREE,       ZERO,  THREE},
	{FOUR,        ZERO,  FOUR},
	{FIVE,        ZERO,  FIVE},
	{SIX,         ZERO,  SIX},
	{SEVEN,       ZERO,  SEVEN},
	{EIGHT,       ZERO,  EIGHT},
	{NINE,        ZERO,  NINE},
	{TEN,         ONE,   ZERO},
	{ELEVEN,      ONE,   ONE},
	{TWELVE,      ONE,   TWO},
	{THIRTEEN,    ONE,   THREE},
	{FOURTEEN,    ONE,   FOUR},
	{FIFTHTEEN,   ONE,   FIVE},
	{SIXTEEN,     ONE,   SIX},
	{SEVENTEEN,   ONE,   SEVEN},
	{EIGHTEEN,    ONE,   EIGHT},
	{NINETEEN,    ONE,   NINE},
	{TWENTY,      TWO,   ZERO},
	{TWENTYONE,   TWO,   ONE},
	{TWENTYTWO,   TWO,   TWO},
	{TWENTYTHREE, TWO,   THREE},
	{TWENTYFOUR,  TWO,   FOUR},
	{TWENTYFIVE,  TWO,   FIVE},
	{TWENTYSIX,   TWO,   SIX},
	{TWENTYSEVEN, TWO,   SEVEN},
	{TWENTYEIGHT, TWO,   EIGHT},
	{TWENTYNINE,  TWO,   NINE},
	{THIRTY,      THREE, ZERO},
	{THIRTYONE,   THREE, ONE},
	{THIRTYTHREE, THREE, TWO},
	{THIRTYTHREE, THREE, THREE},
	{THIRTYFOUR,  THREE, FOUR},
	{THIRTYFIVE,  THREE, FIVE},
	{THIRTYSIX,   THREE, SIX},
	{THIRTYSEVEN, THREE, SEVEN},
	{THIRTYEIGHT, THREE, EIGHT},
	{THIRTYNINE,  THREE, NINE},
	{FOURTY,      FOUR,  ZERO},
	{FOURTYONE,   FOUR,  ONE},
	{FOURTYFOUR,  FOUR,  TWO},
	{FOURTYFOUR,  FOUR,  THREE},
	{FOURTYFOUR,  FOUR,  FOUR},
	{FOURTYFIVE,  FOUR,  FIVE},
	{FOURTYSIX,   FOUR,  SIX},
	{FOURTYSEVEN, FOUR,  SEVEN},
	{FOURTYEIGHT, FOUR,  EIGHT},
	{FOURTYNINE,  FOUR,  NINE},
	{FIFTY,       FIVE,  ZERO},
	{FIFTYONE,    FIVE,  ONE},
	{FIFTYFIVE,   FIVE,  TWO},
	{FIFTYFIVE,   FIVE,  THREE},
	{FIFTYFOUR,   FIVE,  FOUR},
	{FIFTYFIVE,   FIVE,  FIVE},
	{FIFTYSIX,    FIVE,  SIX},
	{FIFTYSEVEN,  FIVE,  SEVEN},
	{FIFTYEIGHT,  FIVE,  EIGHT},
	{FIFTYNINE,   FIVE,  NINE}
};


uint8_t get_table_value(uint8_t unit, uint8_t decimal)
{
	uint8_t ret_val; //output val
	uint8_t i; //counter

	ret_val = FALSE; //default value; false is returned if NAVN

	for(i = ZERO; (TABLE_SIZE-1) > i ; i++)
	{
		/** Verify if the given units and decimals correspond to 0 - 59 **/
		if((key_map[i].unit == unit) && (key_map[i].decimal == decimal))
		{
			ret_val = key_map[i].nval; //merge units and decimals
		}
	}

	return ret_val;
}

void get_table_value_dec2hex(uint8_t number)
{
	global_time.unit = key_map[number].unit;
	global_time.decimal = key_map[number].decimal;
}

uint8_t get_global_unit(void)
{
	return global_time.unit;
}

uint8_t get_global_decimal(void)
{
	return global_time.decimal;
}



