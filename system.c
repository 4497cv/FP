/*
	\file 	  system.c
	\brief	  This program contains the functions that configure the MCU's peripherals and external hardware.
			  It also contains the user menu.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutiérrez, ie705694
	\date	  02/05/2019

     @TODO: implement system's menu using UART interruptions. Polling.
*/

#include "system.h"
#include "clockgating.h"

static terminal_state_t prev_term_st;    //previous terminal state
static terminal_state_t current_term_st; //current  terminal state
static system_state_t current_system_select;
static boolean_t system_start;

static uint8_t keytemp;

static FSM_terminal_t FSM_terminal[TERM_NUM_ST]=
{
	{terminal_menu_start,     {terminal_menu,    terminal_op1,     terminal_op2, terminal_start}},
	{terminal_menu_select,    {terminal_op1,     terminal_op2,   terminal_start,  terminal_menu}},
	{terminal_menu_op1,       {terminal_op2,   terminal_start,    terminal_menu,   terminal_op1}},
	{terminal_menu_op2,       {terminal_start,  terminal_menu,     terminal_op1,   terminal_op2}}
};

static FSM_system_t FSM_system[SYS_NUM_ST]=
{
	{system_play_classic,    {system_GuitarTuner,	 system_PlayerBoard,  system_ClassicMode}},
	{system_guitar_tuner,    {system_PlayerBoard,    system_ClassicMode,  system_GuitarTuner}},
	{system_player_board,    {system_ClassicMode,    system_GuitarTuner,  system_PlayerBoard}}
};

void system_menu(void)
{
	if((TRUE == system_start) && (terminal_start == current_term_st))
	{
		current_term_st = FSM_terminal[current_term_st].next[0]; //show system's menu
		FSM_terminal[current_term_st].fptr(); //invoke state's related function
	}
	else if((TRUE == system_start) && (system_ClassicMode == current_system_select))
	{
		FSM_terminal[terminal_op1].fptr(); //invoke state's related function
		FSM_system[system_ClassicMode].fptr(); //invoke state's related function
	}
	else if((TRUE == system_start) && (system_GuitarTuner == current_system_select))
	{
		FSM_terminal[terminal_op2].fptr(); //invoke state's related function
		FSM_system[system_GuitarTuner].fptr(); //invoke state's related function
		system_start = FALSE;
	}
	else if((TRUE == system_start) && (system_PlayerBoard == current_system_select))
	{
		//FSM_terminal[terminal_menu_op3].fptr(); //invoke state's related function
		FSM_system[system_PlayerBoard].fptr(); //invoke state's related function
	}
	else
	{
		system_start = FALSE;
	}
}


void system_play_classic()
{


}

void system_guitar_tuner()
{

}

void system_player_board()
{

}

void system_select_next_op()
{
	current_system_select = FSM_system[current_system_select].next[0];
}

void system_set_start()
{
	system_start = TRUE;
}

void system_init()
{
	/* System GPIO configuration */
	gpio_pin_control_register_t uart_config = GPIO_MUX3;
	gpio_pin_control_register_t g_input_config = GPIO_MUX1;
	gpio_pin_control_register_t button_config = GPIO_MUX1 | GPIO_PS | GPIO_PE | INTR_FALLING_EDGE;

	const spi_config_t g_spi_config =
	{
			SPI_DISABLE_FIFO,
			SPI_LOW_POLARITY,
			SPI_LOW_PHASE,
			SPI_MSB,
			SPI_0,
			SPI_MASTER,
			GPIO_MUX2,
			SPI_BAUD_RATE_2,
			SPI_FSIZE_8,
			{GPIO_D, bit_1, bit_2}
	};

	/* Enable PORT B clockgating */
	GPIO_clock_gating(GPIO_B);
	/* Enable PORT C clockgating */
	GPIO_clock_gating(GPIO_C);
	/* Enable PORT D clockgating */
	GPIO_clock_gating(GPIO_D);

	/*SPI config*/
	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	LCD_nokia_init(); /*! Configuration function for the LCD */

	/* Set push button start pin configuration */
	GPIO_pin_control_register(GPIO_C, bit_5, &button_config);
	/* drive push button start pin logic */
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_5);

	/* Set push button select pin configuration */
	GPIO_pin_control_register(GPIO_C, bit_7, &button_config);
	/* drive push button select pin logic */
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_7);

	/* ADC configuration */
	ADC_init();

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
	/* Set PORT C interrupt priority */
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_2);
	/* Enable NVIC Interrupts */
	NVIC_global_enable_interrupts;

	current_term_st = terminal_start;
	FSM_terminal[current_term_st].fptr(); //invoke state's related function

	current_term_st = FSM_terminal[current_term_st].next[0]; //set initial terminal state (display menu)
	current_system_st = system_ClassicMode; //set state pointer to classic mode
}


