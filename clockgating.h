/*
 * clockgating.h
 *
 *  Created on: 2 may. 2019
 *      Author: César
 */

#ifndef CLOCKGATING_H_
#define CLOCKGATING_H_

#include "MK64F12.h"
#include "bits.h"

typedef enum
{
    ADC_0,
	ADC_1,
	ADC_2
} ADC_enum_t;

//typedef struct
//{
//
//} CLKG_config_t;

void clockgating_init();
void FTM0_clockgating(void);
void ADC_clockgating(ADC_enum_t adc);

#endif /* CLOCKGATING_H_ */
