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
#include "system.h"

/*\brief Funct used to update the delay funct of the pit
 *\param[add] delay
 * */
void buzzer_update_freq(float delay);

/*\brief Funct to call the toogle of the port used for the buzzer
 *\param[add] void
 * */
void buzzer_toogle(void);

/*\brief Funct that acording to the note will cal the funct buzzer_update_freq for the variation of the buzzer freq
 *\param[add] index
 * */
void note_frequency(uint8_t index);


#endif /* BUZZER_H_ */
