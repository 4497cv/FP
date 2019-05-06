/**
	\file adc.c
	\brief
		This is the source file for the Analog to Digital Converter device driver for Kinetis K64.
		It contains all the implementation for configuration functions and runtime functions.

	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez,ie705694

	\date	  29/03/2019
 */

#include "adc.h"

void ADC_init(void)
{
	gpio_pin_control_register_t config = GPIO_MUX1;

    /** Activate ADC's clock gating **/
    SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;
    /** Activate Port E clock gating **/
    GPIO_clock_gating(GPIO_E);
    /** Configure PORT_E pin 24 **/
  	GPIO_pin_control_register(GPIO_E, bit_24, &config);

    /** Divide ratio is 8 and the clock rate (input clock)/8 **/
    ADC0->CFG1 = ADC_CFG1_ADIV(3);
    /** Long sample time**/
    ADC0->CFG1 |= ADC_CFG1_ADLSMP_MASK;
    /** single-ended 8-bit conversion**/
    ADC0->CFG1 |= ADC_CFG1_MODE(0);
    /** input clock: bus clock **/
    ADC0->CFG1 |= ADC_CFG1_ADICLK(0);

    ADC0->CFG2 = 0;
    ADC0->SC2 = 0;

    /** Hardware average function enabled **/
    ADC0->SC3 = ADC_SC3_AVGE_MASK;
    /** 32 samples of ADC conversions will be averaged **/
    ADC0->SC3 |= ADC_SC3_AVGS(3);
 }

 uint8_t ADC_result(void)
 {
   uint8_t adc_result;
   /** AD12 is selected as input **/
   ADC0->SC1[0] = ADC_SC1_ADCH(bit_17);
   /** Iterate while conversion is not completed **/
   while(0 == (ADC0->SC1[0] & ADC_SC1_COCO_MASK))
   {
	   continue;
   }
   /** Get ADC result **/
   adc_result = ADC0->R[0];
   return(adc_result);
 }

 uint8_t ADC_read(void)
 {
   uint8_t temp;
   uint8_t result;
   temp = ADC_result();
   result = temp;
   return(result);
 }
