/*
	\file 	  frequency_decoder.c
	\brief	  This source file contains functions for the interpration of a guitar signal input.

	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694

	\date	  03/05/2019

	center coordinates 25,10
*/

#include "frequency_decoder.h"

static uint16_t sample_counter = 0;
static float highest_val = 0;
static boolean_t valid_flag;

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

boolean_t FREQ_get_current_note(uint8_t note_number)
{
	uint8_t read_val, i;
	uint8_t temp;
	uint8_t key;
	boolean_t lock_flag;
	uint8_t cadena[STRING_MAX] = {0};
	uint8_t samples_value;
	float voltage_val;
	boolean_t key_flag;
	static boolean_t note_found_f;
	key_flag = FALSE;
	lock_flag = TRUE;
	valid_flag = FALSE;
	sample_counter = 0;


	switch(note_number)
	{
		case C:
			samples_value = 150;
		break;
		case D:
			samples_value = 400;
		break;
		case E:
			samples_value = 300;
		break;
		case F:
			samples_value = 400;
		case G:
			samples_value = 400;
		break;
		case A:
			samples_value = 1;
		break;
		case B:
			samples_value = 400;
		break;
		default:
		break;
	}


	do
	{

		/* get current adc captured value */
		read_val = ADC_read();
		/* conversion to 3.3 V reference */
		voltage_val = (VOLT*read_val)/ADC_MAX;

		if(highest_val < voltage_val)
		{
			highest_val = voltage_val;
		}
		else
		{
			voltage_val = highest_val;
		}

		i = 0;

		do
		{
			temp = (uint8_t) voltage_val;
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

		/* get current key note*/
		key = FREQ_decode_voltage(cadena);
		//printf("%c\n", key);

		
//		FREQ_show_current_voltage(cadena);



		if(samples_value == sample_counter)
		{
			if(key == note_number)
			{
				note_found_f = TRUE;
			}
			else
			{
				note_found_f = FALSE;
			}

			if(valid_flag)
			{
				if(TRUE == note_found_f)
				{
					printf("%c\n", key);
					lock_flag = FALSE;
					key_flag = TRUE;
				}

			}
			sample_counter = 0;
			highest_val = 0;
			//printf("%c\n", key);
		}
		else
		{
			sample_counter++;
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
	valid_flag = FALSE;

	for(i=0; i < KEYMAP_SIZE; i++)
	{
		if((key_map[i].centi == voltage_string[1]) &&
		   (key_map[i].milli == voltage_string[2]) &&
		   (key_map[i].micro == voltage_string[3]) &&
		   (key_map[i].nano == voltage_string[4]))
		{
			index = i;
			valid_flag = TRUE;
			notfound_flag = FALSE;
		}
	}

	if(FALSE == notfound_flag)
	{
		key = key_map[index].key;
	}
	else
	{
		key = 0;
	}

	return key;
}

void FREQ_show_current_voltage(uint8_t voltage_string[STRING_MAX])
{
	printf("Vout = %i.%i%i%i%i V\n", voltage_string[0], voltage_string[1], voltage_string[2], voltage_string[3], voltage_string[4]);
}

void FREQ_voltage_drop()
{
	boolean_t lock_flag;
	uint8_t read_val;
	uint8_t temp;
	uint8_t key;
	uint8_t i;
	volatile uint8_t counter;
	uint8_t cadena[STRING_MAX] = {0};
	float voltage_val;

	lock_flag = TRUE;
	valid_flag = FALSE;
	sample_counter = 0;
	do
	{
		read_val = ADC_read();
		voltage_val = (VOLT*read_val)/ADC_MAX;

		i = 0;

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
		}while(i < 2);

		if((ZERO == cadena[0]) &&
		   (ZERO == cadena[1]))
		{
			lock_flag = FALSE;
		}
		else
		{
			terminal_VoltageDrop();
			counter++;
		}

		//FREQ_show_current_voltage(cadena);
	}while(TRUE == lock_flag);
}

void notedetector()
{
	uint8_t read_val, i;
	uint8_t temp;
	uint8_t key;
	boolean_t lock_flag;
	uint8_t cadena[STRING_MAX] = {0};
	uint16_t samples_value;
	uint16_t samples_c;
	uint8_t counter;
	uint8_t peak_buffer[3];
	float voltage_val;
	boolean_t key_flag;
	static boolean_t note_found_f;
	key_flag = FALSE;
	samples_c = 0;
	lock_flag = TRUE;
	valid_flag = FALSE;
	sample_counter = 0;
	counter = 0;

	switch('B')
	{
		case C:
			samples_value = 150*10;
		break;
		case D:
			samples_value = 130;
		break;
		case E:
			samples_value = 300;
		break;
		case F:
			samples_value = 400;
		case G:
			samples_value = 400;
		break;
		case A:
			samples_value = 30;
		break;
		case B:
			samples_value = 40;
		break;
		default:
		break;
	}


	do
	{

		/* get current adc captured value */
		read_val = ADC_read();
		/* conversion to 3.3 V reference */
		voltage_val = (VOLT*read_val)/ADC_MAX;

		if(highest_val < voltage_val)
		{
			highest_val = voltage_val;
		}
		else
		{
			voltage_val = highest_val;
		}

		i = 0;

		do
		{
			temp = (uint8_t) voltage_val;
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

		/* get current key note*/
		key = FREQ_decode_voltage(cadena);
		//printf("%c\n", key);



		//FREQ_show_current_voltage(cadena);



//		if(valid_flag)
//		{
//				printf("%c\n", key);
//				//lock_flag = FALSE;
//				key_flag = TRUE;
//		}

		if(samples_value == samples_c)
		{
			samples_c = 0;
			peak_buffer[counter] = key;
			counter++;
		}

		if(counter == 3)
		{
			lock_flag = FALSE;
			counter = 0;
		}

		samples_c++;
		sample_counter = 0;
		highest_val = 0;
			//printf("%c\n", key);
		//FREQ_show_current_voltage(cadena);
	}while(TRUE == lock_flag);

	printf("%c, %c, %c\n", peak_buffer[0], peak_buffer[1], peak_buffer[2]);
	return key_flag;
}
