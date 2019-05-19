/*
	\file 	  system.c
	\brief	  This program contains the functions that configure the MCU's peripherals and external hardware.
			  It also contains the user menu.
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694
	\date	  02/05/2019
    Notes: start and select states are changed by the interrupt of port c, by pressing the push buttons.
*/

#include "system.h"
#include "clockgating.h"

static terminal_state_t current_term_st; //current  terminal state
static system_state_t current_system_select;
static boolean_t system_start;
static boolean_t system_select;
static letter_t letter_value;
static uint8_t letter_ascii;
static uint8_t global_username[ID_SIZE];

static FSM_terminal_t FSM_terminal[TERM_NUM_ST]=
{
	{terminal_menu_start,     {terminal_menu,   terminal_menu}},
	{terminal_menu_select0,   {terminal_op1,    terminal_op2}},
	{terminal_menu_op1,       {terminal_op2,    terminal_op1}},
	{terminal_menu_op2,       {terminal_op1,    terminal_op2,}}
};

static FSM_system_t FSM_system[SYSTEM_STATES]=
{
	{system_menu,			 {system_ClassicMode,  system_ClassicMode}},
	{system_play_classic,    {system_PlayerBoard,  system_ClassicMode}},
	{system_player_board,    {system_ClassicMode,  system_PlayerBoard}}
};

void system_menu(void)
{
	/* get current start state */
	system_start = GPIO_get_start_flag();
	/* get current select state */
	system_select = GPIO_get_select_flag();

	/* verify if the start button is pressed */
	if(TRUE == system_start) 
	{
		switch(current_system_select)
		{
			case system_Menu:
				current_term_st = terminal_menu;
			break;
			case system_ClassicMode:
				/* classic mode */
				current_term_st = terminal_op1;
			break;
			case system_PlayerBoard:
				/* playerboard mode */
				current_term_st = terminal_op2;
			break;
			default:
			break;
		}

		/* call corresponding terminal function */
		FSM_terminal[current_term_st].fptr();
		/* call corresponding system function */

		if(system_Menu != current_system_select)
		{
			FSM_system[current_system_select].fptr();
		}

		/* Toggle start button */
		GPIO_toggle_start_flag();
		/* Toggle select button */
		GPIO_toggle_select_flag();
	}
	else if(system_select)
	{
		/* select next system state */
    	system_select_next_op();
		/* show dynamic menu selection */
		system_dynamic_select_handler();
	}
}


void system_play_classic()
{
	/* generate sequence and store it in the global buffer */
	CM_generate_sequence_buffer();
	/* start PIT for adc sampling @ 2kHz */
	PIT_enable_interrupt(PIT_2);
	/* start pit for time interrupt handler */
	PIT_enable_interrupt(PIT_3);
}

void system_user_record_capture(uint8_t sys_time)
{
	/* get current start state */
	system_start = GPIO_get_start_flag();
	/* get current select state */
	system_select = GPIO_get_select_flag();

	sys_time = CM_get_time_g();

	if(TRUE == system_select)
	{
		switch(letter_value)
		{
			case FIRST_LETTER:
				LCD_nokia_goto_xy(25,20);
				LCD_nokia_send_char(letter_ascii);
			break;
			case SECOND_LETTER:
				LCD_nokia_goto_xy(35,20);
				LCD_nokia_send_char(letter_ascii);
			break;
			case THIRD_LETTER:
				LCD_nokia_goto_xy(45,20);
				LCD_nokia_send_char(letter_ascii);
			break;
			default:
			break;
		}
	}
	else if(TRUE == system_start)
	{
		switch(letter_value)
		{
			case FIRST_LETTER:
				letter_value = SECOND_LETTER;
				global_username[FIRST_LETTER] = letter_ascii - ONE;
				letter_ascii = ASCII_A-1;
			break;
			case SECOND_LETTER:
				letter_value = THIRD_LETTER;
				global_username[SECOND_LETTER] = letter_ascii - ONE;
				letter_ascii = ASCII_A-1;
			break;
			case THIRD_LETTER:
				letter_value = SCORE_SAVED;
				global_username[THIRD_LETTER] = letter_ascii - ONE;
				letter_ascii = ASCII_A-1;
			case SCORE_SAVED:
				terminal_score_saved();
				eeprom_store_record(global_username, sys_time);
				/*Funcion para guardar tiempo*/
				reset_menu();
			break;
			default:
			break;
		}
	}


	if(((ASCII_A) <= letter_ascii) && ((ASCII_Z) > letter_ascii))
	{
		letter_ascii++;
	}else
	{
		letter_ascii = ASCII_A;
	}

	GPIO_toggle_start_flag();  //set start flag to false
	GPIO_toggle_select_flag(); //set select flag to false
}

void system_player_board()
{
	EEPROM_read_mem_page();
	terminal_user_score();
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
		case system_PlayerBoard:
			terminal_menu_select2();
		break;
		default:
		break;
	}
}

void system_select_next_op()
{
	current_system_select = FSM_system[current_system_select].next[ZERO];
}

void system_init()
{
	gpio_pin_control_register_t button_config = GPIO_MUX1 | GPIO_PS | GPIO_PE | INTR_FALLING_EDGE;
	gpio_pin_control_register_t i2c_config = GPIO_MUX2|GPIO_PS;

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

	/* ~~~~~~~~ Clock gating activation ~~~~~~~~ */
	/* Enable PORT B clockgating */
	GPIO_clock_gating(GPIO_B);
	/* Enable PORT C clockgating */
	GPIO_clock_gating(GPIO_C);
	/* Enable PORT D clockgating */
	GPIO_clock_gating(GPIO_D);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* ~~~~~~~~~~~~~~ SPI config ~~~~~~~~~~~~~ */
	SPI_init(&g_spi_config); /*! Configuration function for the LCD port*/
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* ~~~~~~~~~ LCD Nokia configuration~~~~~~ */
	LCD_nokia_init(); 
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* ~~~~~~~~~ FlexTimer configuration ~~~~~~ */
	FTM0_output_compare_config();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~ Push Buttons configuration ~~~~~~~*/
	/* Set push button start pin configuration */
	GPIO_pin_control_register(GPIO_C, bit_3, &button_config);
	/* drive push button start pin logic */
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_3);
	/* Set push button select pin configuration */
	GPIO_pin_control_register(GPIO_C, bit_2, &button_config);
	/* drive push button select pin logic */
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_2);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~ I2C configuration ~~~~~~~~~~*/
	/*Set the configuration for i2c_config_Tx*/
	GPIO_pin_control_register(GPIO_B, bit_2, &i2c_config);
	/*Set the configuration for i2c_config_Rx*/
	GPIO_pin_control_register(GPIO_B, bit_3, &i2c_config);
	/*Set the config fot the pin that it will send the i2c protocol*/
	GPIO_data_direction_pin(GPIO_B,GPIO_OUTPUT,bit_2);
	/*Set the config fot the pin that it will receive the i2c protocol*/
	GPIO_data_direction_pin(GPIO_B,GPIO_INPUT,bit_3);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/*~~~~~~~~~~~~ PIT configuration ~~~~~~~~~~*/
	PIT_clock_gating();
	/* Activating PIT */
	PIT_enable();
	/* Set the delay for the pit_1 */
	PIT_delay(PIT_2, SYSTEM_CLOCK, SAMPLING_RATE);   // @ 10 Hz
	PIT_delay(PIT_3, SYSTEM_CLOCK, BPS_RATE);  // @ 1 Hz
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* ~~~~~~~~  ADC configuration ~~~~~~~~ */
	ADC_init();
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/* ~~~~~~~~  I2C configuration ~~~~~~~~ */
	I2C_init(I2C_0, SYSTEM_CLOCK, BD_9600);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(PORTA_IRQ,PRIORITY_5); //SW
	/* Set PORT C interrupt priority */
	NVIC_enable_interrupt_and_priotity(PORTC_IRQ, PRIORITY_5);
	/*Activating the ISR for the PIT and set the priority*/
	NVIC_enable_interrupt_and_priotity(PIT_CH2_IRQ, PRIORITY_3);
	/*Activating the ISR for the PIT and set the priority*/
	NVIC_enable_interrupt_and_priotity(PIT_CH3_IRQ, PRIORITY_2);
	NVIC_global_enable_interrupts;
	
	/*~~~~~~~~~~~~ CALLBACKS configuration ~~~~~~~~~~*/

	/* Callbacks for sampling PIT */
	PIT_callback_init(PIT_2, LM2907_get_current_note);
	/* Callbacks for time PIT */
	PIT_callback_init(PIT_3, CM_handle_time_interrupt);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	current_term_st = terminal_start;
	FSM_terminal[current_term_st].fptr(); //invoke state's related function

	current_term_st = FSM_terminal[current_term_st].next[ZERO]; //set initial terminal state (display menu)
	current_system_select = system_Menu; //set state pointer to classic mode
	CM_reset_game();
}

void reset_menu()
{
	FSM_terminal[terminal_menu].fptr();
	current_system_select = system_Menu; //set state pointer to classic mode
	letter_ascii = ASCII_A-1;
	letter_value = FIRST_LETTER;
	GPIO_toggle_playerboard_flag();
	CM_reset_game();
}


