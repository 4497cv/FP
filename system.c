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
static system_state_t current_system_st;

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
	{system_play_classic,    {system_op2,	 system_op1}},
	{system_guitar_tuner,    {system_op1,    system_op2}}
};

void system_menu(void)
{
	boolean_t mailbox_flag;
	boolean_t menu_select_flag;
	uint8_t mailbox_value;

	mailbox_flag = UART_get_mailbox_flag(UART_0);

	if(mailbox_flag)
	{
		mailbox_value = UART_get_mailbox(UART_0); //get mailbox value
		menu_select_flag = valid_menu_select(mailbox_value);

		if(menu_select_flag)
		{
			switch(keytemp)
			{
				case ASCII_ONE:
					current_term_st = terminal_op1;
					current_system_st = system_op1;
				break;
				case ASCII_TWO:
					current_term_st = terminal_op2;
					current_system_st = system_op2;
				case ASCII_ESC:
					current_term_st = terminal_menu;
				break;
				default:
				break;
			}

			system_fsm_handler();
		}
		else
		{

		}

	}

	UART_empty_mailbox(UART_0);
	//UART_empty_mailbox(UART_0);
//	current_term_st = FSM_terminal[current_term_st].next[0]; //set initial terminal state (display menu)
//	FSM_terminal[current_term_st].fptr(); //invoke state's related function

}

void system_init()
{
	/* System GPIO configuration */
	gpio_pin_control_register_t uart_config = GPIO_MUX3;
	gpio_pin_control_register_t g_input_config = GPIO_MUX1;
	GPIO_clock_gating(GPIO_B);
	GPIO_clock_gating(GPIO_C);

	/**Configures the pin control register of pin16 in PortB as UART RX*/
	GPIO_pin_control_register(GPIO_B, bit_16, &uart_config);
	/**Configures the pin control register of pin16 in PortB as UART TX*/
	GPIO_pin_control_register(GPIO_B, bit_17, &uart_config);

	GPIO_pin_control_register(GPIO_C, bit_9, &g_input_config);
	/* Set pin as input */
	GPIO_data_direction_pin(GPIO_C, GPIO_INPUT, bit_9);

	/* FTM configuration */
	FTM0_clockgating();
	FTM_config();

	/* UART config */
	/**Configures UART 0 to transmit/receive at 11520 bauds with a 21 MHz of clock core*/
	UART_init (UART_0, SYSTEM_CLOCK, BD_115200);
	/**Enables the UART 0 interrupt*/
	UART_interrupt_enable(UART_0);

	/**Sets the threshold for interrupts, if the interrupt has higher priority constant that the BASEPRI, the interrupt will not be attended*/
	NVIC_set_basepri_threshold(PRIORITY_10);
	NVIC_enable_interrupt_and_priotity(UART0_IRQ, PRIORITY_2);
	/**Enables and sets a particular interrupt and its priority*/
	NVIC_enable_interrupt_and_priotity(FTM3_IRQ, PRIORITY_5);
	NVIC_global_enable_interrupts;

	prev_term_st = terminal_start;
	FSM_terminal[prev_term_st].fptr(); //invoke state's related function

	current_term_st = terminal_menu; //set initial terminal state (display menu)
}

boolean_t valid_menu_select(uint8_t mailbox_value)
{
	boolean_t ver_flag;

	/** Verify if the keypressed is a numeric option for the switch case **/
	if((ASCII_ONE <= mailbox_value) && (ASCII_TWO>= mailbox_value)) //CHANGED
	{
		keytemp = mailbox_value;
		ver_flag = FALSE;
		/** Display pressed key on screen **/
		UART_put_char(UART_0, mailbox_value);
	}
	else if(ASCII_ENTER == mailbox_value)
	{
		ver_flag = TRUE;
	}
	else if(ASCII_ESC == mailbox_value)
	{
		ver_flag = FALSE;
		keytemp = mailbox_value;
	}
	else
	{
		UART_empty_mailbox(UART_0);
		ver_flag = FALSE;
	}

	return ver_flag;
}

void system_play_classic()
{
}

void system_guitar_tuner()
{

}

void system_fsm_handler()
{
	if(prev_term_st != current_term_st)
	{
		FSM_terminal[current_term_st].fptr(); //invoke state's related function
		//FSM_system[current_system_st].fptr();
		prev_term_st = current_term_st;
	}
	else
	{

	}
}
