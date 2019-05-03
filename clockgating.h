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

//typedef struct
//{
//
//} CLKG_config_t;

void clockgating_init();
void FTM0_clockgating(void);

#endif /* CLOCKGATING_H_ */
