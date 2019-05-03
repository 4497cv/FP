/**
	\file flextimer.c
	\brief This is the source file for the Flex Timer device driver for Kinetis K64.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez,ie705694
	\date	  02/05/2019
 */

#include "FlexTimer.h"

static ftm_state_t current_state;
static uint32_t current_freq;
static float temp_s0;
static float temp_s1;

static FSM_FlexTimer_t FSM_FlexTimer[FLEX_NUM_ST]=
{
	{&temp_s0, &FTM3->CONTROLS[5].CnV, {FTM_S1, FTM_S0}},
	{&temp_s1, &FTM3->CONTROLS[5].CnV, {FTM_S0, FTM_S1}}
};

void FTM3_IRQHandler()
{
	uint32_t freq;
	float diff;
	
	/* Turn off Channel event flag */
	FTM3->CONTROLS[5].CnSC &= ~FLEX_TIMER_CHF;
	
	/* Get the current channel value and set it to the temporary value of the current state */
	*FSM_FlexTimer[current_state].tempval = *FSM_FlexTimer[current_state].ChannelValue;

	if(*FSM_FlexTimer[FTM_S0].tempval > *FSM_FlexTimer[FTM_S1].tempval)
	{
		/* Add previous val to next value if smaller */
		*FSM_FlexTimer[FTM_S1].tempval += *FSM_FlexTimer[FTM_S0].tempval;
	}

	/* Calculate the difference between captured values to get the period */
	diff = *FSM_FlexTimer[FTM_S1].tempval - *FSM_FlexTimer[FTM_S0].tempval;
    /* Frequency is the equivalent of the inverse of the period */
	freq = 1/(diff/(FREQ_PS));

	/* We assure we don't get any negative values */
	if(NEGATIVE != freq)
	{
		current_freq = freq;
	}

	/* Get next state */
	current_state = FSM_FlexTimer[current_state].next[0];
}

void FTM_config()
{
	current_state = FTM_S0;
	/*Clock gating for the FTM3*/
	SIM->SCGC3 |= SIM_SCGC3_FTM3_MASK;

	/*FTM enable
	 * This field is write protected. It can be written only when MODE[WPDIS] = 1.
	 * 0 Only the TPM-compatible registers (first set of registers) can be used without any restriction. Do not
	   use the FTM-specific registers.
	 * 1 All registers including the FTM-specific registers (second set of registers) are available for use with no
	   restrictions.*/
	FTM3->MODE &= ~FLEX_TIMER_FTMEN;

	/**Selects the FTM behavior in BDM mode.In this case in functional mode*/
	FTM3->CONF |= FTM_CONF_BDMMODE(3);

	/*Clears SC*/
	FTM3->SC = 0x0;

	/*ELSA -> capture on rising edge */
	FTM3->CONTROLS[5].CnSC |= FLEX_TIMER_ELSA;

	/*Clear Combine*/
	FTM3->COMBINE = 0x0;

	/*CHIE (Channel Interrupt Enable)
	 * 0 Disable channel interrupts. Use software polling.
	 * 1 Enable channel interrupts.*/
	FTM3->CONTROLS[5].CnSC |= FTM_CnSC_CHIE_MASK;

	/**Assigning a default value for modulo register*/
	FTM3->MOD |= FTM_MOD_MOD_MASK;

	/**Select clock source and prescaler*/
	FTM3->SC |= FLEX_TIMER_CLKS_1 | FLEX_TIMER_PS_64;
}
