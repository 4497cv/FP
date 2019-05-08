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
static boolean_t system_select;

static FSM_terminal_t FSM_terminal[TERM_NUM_ST]=
{
	{terminal_menu_start,     {terminal_menu,   terminal_op1,     terminal_op2,   terminal_start}},
	{terminal_menu_select0,   {terminal_op1,    terminal_op2,     terminal_op3,   terminal_op4}},
	{terminal_menu_op1,       {terminal_op2,    terminal_op3,     terminal_op4,   terminal_op1}},
	{terminal_menu_op2,       {terminal_op3,    terminal_op4,     terminal_op1,   terminal_op2}},
	{terminal_menu_op3,       {terminal_op4,    terminal_op1,     terminal_op2,   terminal_op3}},
	{terminal_menu_op4,       {terminal_op1,    terminal_op2,     terminal_op3,   terminal_op4}}
};

static FSM_system_t FSM_system[SYS_NUM_ST]=
{
	{system_menu,			 {system_ClassicMode,  system_GuitarTuner,      system_PlayerBoard,   system_ClassicMode}},
	{system_play_classic,    {system_SimonMode,    system_GuitarTuner,      system_PlayerBoard,   system_ClassicMode}},
	{system_play_SimonMode,  {system_GuitarTuner,  system_PlayerBoard,      system_ClassicMode,   system_SimonMode}},
	{system_guitar_tuner,    {system_PlayerBoard,  system_PlayerBoard,      system_ClassicMode,   system_GuitarTuner}},
	{system_player_board,    {system_ClassicMode,  system_SimonMode,        system_GuitarTuner,   system_PlayerBoard}}
};

void system_menu(void)
{

	system_start = get_start_flag();
	system_select = get_select_flag();


	if(TRUE == system_start)
	{
		switch(current_system_select)
		{
			case system_ClassicMode:
				current_term_st = terminal_op1;
			break;
			case system_SimonMode:
				current_term_st = terminal_op2;
			break;
			case system_GuitarTuner:
				current_term_st = terminal_op3;
			break;
			case system_PlayerBoard:
				current_term_st = terminal_op4;
			break;
			default:
			break;
		}

		FSM_terminal[current_term_st].fptr();
		FSM_system[current_system_select].fptr();

		system_start = FALSE;
		toggle_start_flag();
		toggle_select_flag();
	}
	else if(system_select)
	{
    	system_select_next_op();
		system_dynamic_select_handler();
	}

//	if(prev_term_st != current_term_st)
//	{
//		FSM_terminal[current_term_st].fptr();
//		FSM_system[current_system_select].fptr();
//		prev_term_st = current_term_st;
//	}
}


void system_play_classic()
{


}

void system_play_SimonMode()
{
	generate_sequence_buffer();

}

void system_guitar_tuner()
{

}

void system_dynamic_select_handler(void)
{
	switch(current_system_select)
	{
		case system_Menu:
			terminal_menu_select0();
		break;
		case system_ClassicMode:
			terminal_menu_select1();
		break;
		case system_SimonMode:
			terminal_menu_select2();
		break;
		case system_GuitarTuner:
			terminal_menu_select3();
		break;
		case system_PlayerBoard:
			terminal_menu_select4();
		break;
		default:
		break;
	}
}

void system_player_board()
{

}

void system_select_next_op()
{
	current_system_select = FSM_system[current_system_select].next[0];
}

void system_init()
{
	/* System GPIO configuration */
	gpio_pin_control_register_t uart_config = GPIO_MUX3;
	gpio_pin_control_register_t g_input_config = GPIO_MUX1;
	gpio_pin_control_register_t button_config = GPIO_MUX1 | GPIO_PS | GPIO_PE | INTR_FALLING_EDGE;
	gpio_pin_control_register_t output_pit_config = GPIO_MUX1;

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

	FTM0_output_compare_config();
	buzzer_config();

	/* Set push button start pin configuration */
	GPIO_pin_control_register(GPIO_C, bit_3, &button_config);
	/* drive push button start pin logic */
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_3);

	/* Set push button select pin configuration */
	GPIO_pin_control_register(GPIO_C, bit_2, &button_config);
	/* drive push button select pin logic */
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_2);

	/**Pin control configuration of GPIOB pin0 as GPIO*/
	GPIO_pin_control_register(GPIO_C,bit_5,&output_pit_config);
	/**Assigns a safe value to the output pin*/
	GPIO_set_pin(GPIO_C,bit_5);
	/**Configures GPIOD pin0 as output*/
	GPIO_data_direction_pin(GPIO_C,GPIO_OUTPUT,bit_5);
	GPIO_clear_pin(GPIO_C,bit_5);

	PIT_clock_gating();
	/**Activating PIT*/
	PIT_enable();
	/*Set the delay for the pit_1*/
	PIT_delay(PIT_0, SYSTEM_CLOCK, DELAY);


	/* ADC configuration */
	ADC_init();

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_5); //SW
	/* Set PORT C interrupt priority */
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_5);
	/*Activating the ISR for the PIT and set the priority*/
	NVIC_enable_interrupt_and_priotity(PIT_CH0_IRQ, PRIORITY_6);
	/*Activating the ISR for the PIT and set the priority*/
	NVIC_enable_interrupt_and_priotity(PIT_CH1_IRQ, PRIORITY_6);
	/** Callbacks for PIT */
	PIT_callback_init(PIT_0,send_sequence_buzzer);
	/* Enable NVIC Interrupts */
	NVIC_global_enable_interrupts;

	current_term_st = terminal_start;
	FSM_terminal[current_term_st].fptr(); //invoke state's related function

	current_term_st = FSM_terminal[current_term_st].next[0]; //set initial terminal state (display menu)
	current_system_select = system_Menu; //set state pointer to classic mode
}


