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
static boolean_t note_found_f = FALSE;
static uint8_t current_note_g;
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

void update_current_note(uint8_t note)
{
	current_note_g = note;
}
void FREQ_get_current_note(void)
{
	float voltage_val; //voltage value read
	uint8_t digital_val; //digital value read
	uint8_t index; //string's index
	uint8_t temp;  //voltage integer round-up
	uint8_t key;   //voltage to keynote conversion value
	uint8_t cadena[STRING_MAX] = {0}; //string that contains voltage
	
	/* get current adc captured value */
	digital_val = ADC_read();

	/* conversion to 3.3 V reference */
	voltage_val = (ANALOG_LIMIT*digital_val)/DIGITAL_LIMIT;



	
	/*
	 * VERIFY IF NUMERIC SHIFT IS RIGHT
	*/

	index = 0;
	do
	{
		temp = (uint8_t) voltage_val;
		cadena[index] = temp;
		index++;

		voltage_val = voltage_val - temp;
		voltage_val = voltage_val * 10;

		temp = (uint8_t) voltage_val;
		cadena[index] = temp;
		index++;

		voltage_val = voltage_val - temp;
		voltage_val = voltage_val * 10;

		temp = (uint8_t) voltage_val;
		cadena[index] = temp;
	}while(index < 5);


	/* get current key note*/
	key = FREQ_decode_voltage(cadena);


	//FREQ_show_current_voltage(cadena);
	//printf("%c\n", key);
	/* verify if the note played coincides with current note status value */
	update_note_found_flag_status(key);

	sample_counter++;

}

void update_highest_voltage_value(uint8_t voltage_val)
{
	/* keep highest voltage value */
	if(highest_val < voltage_val)
	{
		highest_val = voltage_val;
	}
	else
	{
		/* do nothing */
	}
}

void update_note_found_flag_status(uint8_t key)
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

uint8_t get_note_found_flag(void)
{
	return note_found_f;
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
			notfound_flag = FALSE;
			valid_flag = TRUE;
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

