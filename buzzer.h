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
#include "simon_says.h"

#define SYSTEM_CLOCK (21000000U)
#define DELAY (1.0F)

void buzzer_update_freq(float delay);

void buzzer_toogle(void);

void note_frequency(uint8_t index);


#endif /* BUZZER_H_ */
