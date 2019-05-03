/*
 * clockgating.c
 *
 *  Created on: 2 may. 2019
 *      Author: César
 */

#include "clockgating.h"

void FTM0_clockgating(void)
{
	/** Clock gating for the FlexTimer 0*/
	SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;
}
