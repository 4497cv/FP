/*
	\file 	  LM2907.c
	\brief	  This source file contains functions for the frequency to voltage converter module.
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  03/05/2019
*/

#include "LM2907.h"

static boolean_t note_found_f = FALSE;
static uint8_t current_note_g;

static const Keymap_t key_map[KEYMAP_SIZE]=
{
	{'C',   C1_1, C1_2, C1_3, C1_4}, /*  DO  */
	{'D',   D1_1, D1_2, D1_3, D1_4}, /*  RE  */
	{'E',   E1_1, E1_2, E1_3, E1_4}, /*  MI  */
	{'F',   F1_1, F1_2, F1_3, F1_4}, /*  FA  */
	{'G',   G1_1, G1_2, G1_3, G1_4}, /*  SOL */
	{'A',   A1_1, A1_2, A1_3, A1_4}, /*  LA  */
	{'B',   B1_1, B1_2, B1_3, B1_4}  /*  SI  */
};

void LM2907_get_current_note(void)
{
	float voltage_val; //voltage value read
	uint8_t digital_val; //digital value read
	uint8_t index; //string's index
	uint8_t temp;  //voltage integer round-up
	uint8_t key;   //voltage to keynote conversion value
	uint8_t voltage_string[STRING_MAX] = {ZERO}; //string that contains voltage
	
	/* get current adc captured value */
	digital_val = ADC_read();

	/* conversion to 3.3 V reference */
	voltage_val = (ANALOG_LIMIT*digital_val)/DIGITAL_LIMIT;

	index = 0;

	do
	{
		temp = (uint8_t) voltage_val;
		voltage_string[index] = temp;
		index++;

		voltage_val = voltage_val - temp;
		voltage_val = voltage_val * 10;

		temp = (uint8_t) voltage_val;
		voltage_string[index] = temp;
		index++;

		voltage_val = voltage_val - temp;
		voltage_val = voltage_val * 10;

		temp = (uint8_t) voltage_val;
		voltage_string[index] = temp;
	}while(index < 5);

	/* get current key note*/
	key = LM2907_decode_voltage(voltage_string[ONE], voltage_string[TWO], voltage_string[THREE]);

	/* verify if the note played coincides with current note status value */
	LM2907_update_note_found_flag_status(key);
}

uint8_t LM2907_decode_voltage(uint8_t voltage_string1, uint8_t voltage_string2,uint8_t voltage_string3)
{
	uint8_t i;
	uint8_t index;
	uint8_t key;
	boolean_t notfound_flag;

	notfound_flag = TRUE;

	for(i = ZERO; KEYMAP_SIZE > i ; i++)
	{
		if((key_map[i].centi == voltage_string1) &&
		   (key_map[i].milli == voltage_string2) &&
		   (key_map[i].micro == voltage_string3))
		{
			index = i;
			notfound_flag = FALSE;
		}
	}

	if(FALSE == notfound_flag)
	{
		key = key_map[index].key;
	}
	else
	{
		key = ZERO;
	}

	return key;
}

void LM2907_update_note_found_flag_status(uint8_t key)
{
	if((key == current_note_g) && (current_note_g != ZERO))
	{
		note_found_f = TRUE;
	}
	else
	{
		note_found_f = FALSE;
	}
}

boolean_t LM2907_get_note_found_flag(void)
{
	return note_found_f;
}

void LM2907_update_current_note(uint8_t note)
{
	current_note_g = note;
}

void LM2907_show_current_voltage(uint8_t voltage_string[STRING_MAX])
{
#ifndef DEBUG
	printf("Vout = %i.%i%i%i%i V\n", voltage_string[ZERO], voltage_string[ONE], voltage_string[TWO], voltage_string[THREE], voltage_string[FOUR]);
#endif
}

void LM2907_show_current_key(uint8_t key)
{
#ifndef DEBUG
	printf("%c\n", key);
#endif
}

