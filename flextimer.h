/**
	\file flextimer.h
	\brief
		This is the source file for the flextimer device driver for Kinetis K64.

	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez,ie705694

	\date	  29/03/2019
 */

#ifndef FLEXTIMER_H_
#define FLEXTIMER_H_

#include "MK64F12.h"
#include "Bits.h"
#include "GPIO.h"
#include <stdint.h>
#include "system.h"

#define FLEX_TIMER_0_CLOCK_GATING 0x01000000

#define FLEX_TIMER_FAULTIE  0x80
#define FLEX_TIMER_FAULTM_0   0x00
#define FLEX_TIMER_FAULTM_1   0x20
#define FLEX_TIMER_FAULTM_2   0x40
#define FLEX_TIMER_FAULTM_3   0x60
#define FLEX_TIMER_CAPTEST  0x10
#define FLEX_TIMER_PWMSYNC  0x08
#define FLEX_TIMER_WPDIS    0x04
#define FLEX_TIMER_INIT     0x02
#define FLEX_TIMER_FTMEN    0x01

#define FLEX_TIMER_TOF     0x80
#define FLEX_TIMER_TOIE    0x40
#define FLEX_TIMER_CPWMS   0x20
#define FLEX_TIMER_CLKS_0  0x00
#define FLEX_TIMER_CLKS_1  0x08
#define FLEX_TIMER_CLKS_2  0x10
#define FLEX_TIMER_CLKS_3  0x18
#define FLEX_TIMER_PS_1    0x00
#define FLEX_TIMER_PS_2    0x01
#define FLEX_TIMER_PS_4    0x02
#define FLEX_TIMER_PS_8    0x03
#define FLEX_TIMER_PS_16    0x04
#define FLEX_TIMER_PS_32    0x05
#define FLEX_TIMER_PS_64    0x06
#define FLEX_TIMER_PS_128    0x07

#define FLEX_TIMER_PWMLOAD_CH0 0x01
#define FLEX_TIMER_PWMLOAD_CH1 0x02
#define FLEX_TIMER_PWMLOAD_CH2 0x04
#define FLEX_TIMER_PWMLOAD_CH3 0x08
#define FLEX_TIMER_PWMLOAD_CH4 0x10
#define FLEX_TIMER_PWMLOAD_CH5 0x20
#define FLEX_TIMER_PWMLOAD_CH6 0x40
#define FLEX_TIMER_PWMLOAD_CH7 0x80
#define FLEX_TIMER_LDOK        0x200

#define  FLEX_TIMER_DMA   0x01
#define  FLEX_TIMER_ELSA  0x04
#define  FLEX_TIMER_ELSB  0x08
#define  FLEX_TIMER_MSA   0x10
#define  FLEX_TIMER_MSB   0x20
#define  FLEX_TIMER_CHIE  0x40
#define  FLEX_TIMER_CHF   0x80

#define FTM_ULIMIT 0x00FA
#define FTM_LLIMIT 0x0005

#define FTM_RST_ULIMIT 0x00FF
#define FTM_RST_LLIMIT 0x0000

#define FTM_OFF 0
#define FTM_ON 255
#define NEGATIVE -1

//
#define FLEX_NUM_ST 2
#define FREQ_PS SYSTEM_CLOCK/64

typedef enum
{
	FTM_S0,
	FTM_S1
} ftm_state_t;

typedef struct
{
	float *tempval;
	volatile uint32_t *ChannelValue;
	ftm_state_t next[2];
} FSM_FlexTimer_t;


/*!
 	 \brief This function set the minimum configuration so the FTM can work.

 	 \param[in]
 	 \return void
 	 \todo
 */
void FTM_config();




#endif /* FLEXTIMER_H_ */
