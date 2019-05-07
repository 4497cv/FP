/*
 * buzzer.h
 *
 *  Created on: May 7, 2019
 *      Author: LuisFernando
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "FlexTimer.h"
#include "gpio.h"
#include "pit.h"

void buzzer_config(void);

void buzzer_update_freq(float delay);

void buzzer_toogle(void);


#endif /* BUZZER_H_ */
