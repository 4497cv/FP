/*
 * frequency_decoder.c
 *
 *  Created on: 3 may. 2019
 *      Author: César
 */


#include "frequency_decoder.h"
static uint8_t sample_counter = 0;
static float highest_val = 0;
static boolean_t valid_flag;

Keymap_t key_map[KEYMAP_SIZE]=
{
 {'C',   C1_1, C1_2, C1_3, C1_4}, /*  DO  */
 {'D',   D1_1, D1_2, D1_3, D1_4}, /*  RE  */
 {'E',   E1_1, E1_2, E1_3, E1_4}, /*  MI  */
 {'F',   F1_1, F1_2, F1_3, F1_4}, /*  FA  */
 {'G',   G1_1, G1_2, G1_3, G1_4}, /*  SOL */
 {'A',   A1_1, A1_2, A1_3, A1_4}, /*  LA  */
 {'B',   B1_1, B1_2, B1_3, B1_4}  /*  SI  */
};

boolean_t FREQ_get_current_note(uint8_t note_number)
{
	uint8_t read_val, i;
	uint8_t temp;
	uint8_t key;
	boolean_t lock_flag;
	uint8_t number_decoded;
	uint8_t cadena[STRING_MAX] = {0};
	float voltage_val;
	boolean_t key_flag;
	key_flag = FALSE;
	lock_flag = TRUE;
	valid_flag = FALSE;

	do
	{
		read_val = ADC_read();
		voltage_val = (VOLT*read_val)/ADC_MAX;

		if(highest_val < voltage_val)
		{
			highest_val = voltage_val;
		}
		else
		{
			voltage_val = highest_val;
		}

		sample_counter++;
		i=0;

		do
		{
			temp = (uint8_t)voltage_val;
			cadena[i] = temp;
			i++;

			voltage_val = voltage_val - temp;
			voltage_val = voltage_val * 10;

			temp = (uint8_t)voltage_val;
			cadena[i] = temp;
			i++;

			voltage_val = voltage_val - temp;
			voltage_val = voltage_val * 10;

			temp = (uint8_t)voltage_val;
			cadena[i] = temp;
		}while(i < 5);

		key = FREQ_decode_voltage(cadena);

		number_decoded = SS_note_convert_to_number(key);
		//FREQ_show_current_voltage(cadena);
		if(NSAMPLES == sample_counter)
		{
			sample_counter = 0;
			highest_val = 0;
			if(TRUE == valid_flag && number_decoded == note_number)
			{
				printf("%c\n", key);
				lock_flag = FALSE;
				key_flag = TRUE;
			}
		}

		//FREQ_show_current_voltage(cadena);
	}while(TRUE == lock_flag);

	return key_flag;
}

uint8_t FREQ_decode_voltage(uint8_t voltage_string[STRING_MAX])
{
	uint8_t i;
	uint8_t index;
	uint8_t key;
	boolean_t notfound_flag;

	notfound_flag = TRUE;

	for(i=0; i < KEYMAP_SIZE; i++)
	{
		if((key_map[i].centi == voltage_string[1]) &&
		   (key_map[i].milli == voltage_string[2]) &&
		   (key_map[i].micro == voltage_string[3]) &&
		   (key_map[i].nano == voltage_string[4]))
		{
			index = i;
			notfound_flag = FALSE;
			valid_flag = TRUE;
		}
	}

	if(TRUE == notfound_flag)
	{
		key = 0;
	}
	else
	{
		key = key_map[index].key;
	}

	return key;
}

void FREQ_show_current_voltage(uint8_t voltage_string[STRING_MAX])
{
	printf("Vout = %i.%i%i%i%i V\n", voltage_string[0], voltage_string[1], voltage_string[2], voltage_string[3], voltage_string[4]);
}

void FREQ_voltage_drop()
{
	uint8_t read_val, i;
	uint8_t temp;
	uint8_t key;
	boolean_t lock_flag;
	uint8_t cadena[STRING_MAX] = {0};
	float voltage_val;

	lock_flag = TRUE;
	valid_flag = FALSE;

	do
	{
		read_val = ADC_read();
		voltage_val = (VOLT*read_val)/ADC_MAX;

		if(highest_val < voltage_val)
		{
			highest_val = voltage_val;
		}
		else
		{
			voltage_val = highest_val;
		}

		sample_counter++;
		i=0;

		do
		{
			temp = (uint8_t)voltage_val;
			cadena[i] = temp;
			i++;

			voltage_val = voltage_val - temp;
			voltage_val = voltage_val * 10;

			temp = (uint8_t)voltage_val;
			cadena[i] = temp;
			i++;

			voltage_val = voltage_val - temp;
			voltage_val = voltage_val * 10;

			temp = (uint8_t)voltage_val;
			cadena[i] = temp;
		}while(i < 5);

		if(cadena[0] == 0 && cadena[1] == 0 && cadena[2] == 0 && cadena[3] == 0)
		{
			lock_flag = FALSE;
		}

		//FREQ_show_current_voltage(cadena);
	}while(TRUE == lock_flag);

}
