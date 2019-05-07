/**
	\file adc.h
	\brief
		This is the header file for the Analog to Digital Converter device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.

	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez,ie705694

	\date	  29/03/2019
 */

#ifndef adc_H_
#define adc_H_

#include "stdint.h"
#include "gpio.h"
#include "bits.h"
#include "MK64F12.h"

#define VOLT 3.3F
#define ADC_MAX 255

void ADC_init(void);
uint8_t ADC_result(void);
uint8_t ADC_read(void);

#endif
