/*
 * k64_push_buttons.c
 *
 *  Created on: May 6, 2019
 *      Author: LuisFernando
 */

#include "k64_system.h"

void gpio_push_button(void)
{
/*GPIO config*/
	gpio_pin_control_register_t input_intr_config = GPIO_MUX1 | GPIO_PS | GPIO_PE | INTR_FALLING_EDGE;
	/**Activating the GPIO_A/GPIO_C clock gating*/
	GPIO_clock_gating(GPIO_A);
	GPIO_clock_gating(GPIO_C);

	/**Pin control configuration of GPIOA pin4 as GPIO/Intr*/
	GPIO_pin_control_register(GPIO_A,bit_4,&input_intr_config);
	/**Pin control configuration of GPIOC pin6 as GPIO/Intr*/
	GPIO_pin_control_register(GPIO_C,bit_6,&input_intr_config);

	/**Configures GPIOA pin4 as input*/
	GPIO_data_direction_pin(GPIO_A,GPIO_INPUT,bit_4);
	/**Configures GPIOC pin6 as input*/
	GPIO_data_direction_pin(GPIO_C,GPIO_INPUT,bit_6);
}
