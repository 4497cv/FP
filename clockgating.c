/*
	\file 	  clockgating.c
	\brief	  
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  02/05/2019
*/

#include "clockgating.h"

void FTM0_clockgating(void)
{
	/** Clock gating for the FlexTimer 0*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
}

void ADC_clockgating(ADC_enum_t adc_num)
{
	switch(adc_num)
	{
		case ADC_0:
			/** Activate ADC's clock gating **/
			SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
		break;
		default:
		break;
	}
}
