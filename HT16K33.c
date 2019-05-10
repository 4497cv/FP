/**
	\file 	  HT16K33.c
	\brief
			  This is the source file for the matrix module. It contains functions
			  for the operation of the M1707042 8*8 LED matrix.
	\authors: César Villarreal Hernández, ie707560
	          Luís Fernando Rodríguez Gutiérrez, ie705694

	\date	  28/04/2019
	Graphics created using: http://robojax.com/learn/arduino/8x8LED/
 */

#include <HT16K33.h>

static led_HT16K33_t global_matrix = {0};

/** Table containing the information that relates row values and numeric data **/
static time_display_t display_info[0] =
{

};

/** Table contains data for animations **/
static time_display_t display_startup[1] =
{
	{SQ_START,    0b11111111,  0b10000001,  0b10111101,  0b10100101,  0b10100101,  0b10111101,  0b10000001,  0b11111111}
};

const I2C_state_t FSM_Moore[5]=
{
	{I2C_TX,   HT16K33_WRITE_CONTROL,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S0}}, //WRITE CONTROL STATE
    {I2C_TX,    HT16K33_OSC_CONTROL1,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S0, HT16K33_I2C_S1}}, //SET ADDRESS STATE
	{I2C_TX,    HT16K33_OSC_CONTROL2,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S3, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2}}, //WRITE DATA STATE
	{I2C_TX,    HT16K33_OSC_CONTROL3,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3}}, //WRITE DATA STATE
	{I2C_TX,         HT16K33_ADDRESS,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3}} //WRITE DATA STATE
};

const I2C_D_state_t FSM_Display1[8]=
{
    {I2C_TX,   &global_matrix.led_display_1[row_0],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1}},
	{I2C_TX,   &global_matrix.led_display_1[row_1],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2}},
	{I2C_TX,   &global_matrix.led_display_1[row_2],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3}},
	{I2C_TX,   &global_matrix.led_display_1[row_3],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4}},
	{I2C_TX,   &global_matrix.led_display_1[row_4],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5}},
	{I2C_TX,   &global_matrix.led_display_1[row_5],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6}},
	{I2C_TX,   &global_matrix.led_display_1[row_6],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7}},
	{I2C_TX,   &global_matrix.led_display_1[row_7],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S8}}
};

const I2C_D_state_t FSM_Display2[8]=
{
    {I2C_TX,   &global_matrix.led_display_2[row_0],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1}},
	{I2C_TX,   &global_matrix.led_display_2[row_1],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2}},
	{I2C_TX,   &global_matrix.led_display_2[row_2],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3}},
	{I2C_TX,   &global_matrix.led_display_2[row_3],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4}},
	{I2C_TX,   &global_matrix.led_display_2[row_4],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5}},
	{I2C_TX,   &global_matrix.led_display_2[row_5],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6}},
	{I2C_TX,   &global_matrix.led_display_2[row_6],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S7, HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7}},
	{I2C_TX,   &global_matrix.led_display_2[row_7],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {HT16K33_I2C_S0, HT16K33_I2C_S1, HT16K33_I2C_S2, HT16K33_I2C_S3, HT16K33_I2C_S4, HT16K33_I2C_S5, HT16K33_I2C_S6, HT16K33_I2C_S7, HT16K33_I2C_S8}}
};


void HT16K33_init(void)
{
	uint8_t	current_state;
	uint8_t tx_or_rx;
	uint8_t writebyte;

	/** Set current state to first command **/
	current_state = HT16K33_I2C_S1;
	/** Enable transmission **/
	tx_or_rx = FSM_Moore[current_state].Transmit_Receive;
	FSM_Moore[current_state].fptrTxRx(tx_or_rx); //Enable transmission

	do
	{
		if(HT16K33_I2C_S1 == current_state)
		{
			/** Generate start signal **/
			FSM_Moore[current_state].start();
		}
		else
		{
			/** Generate repeated start signal **/
			I2C_repeated_start();
		}

		writebyte = FSM_Moore[HT16K33_I2C_S0].writebyte;		//Retrieve current writebyte value
		FSM_Moore[HT16K33_I2C_S0].fptrWrite(writebyte);		//Send writebyte current value
		FSM_Moore[HT16K33_I2C_S0].fptrWaitTransfer();		//wait until transfer is complete
		FSM_Moore[HT16K33_I2C_S0].fptrgetAck();				//receive acknowledge

		writebyte = FSM_Moore[current_state].writebyte;		//Retrieve current writebyte value
		FSM_Moore[current_state].fptrWrite(writebyte);		//Send writebyte current value
		FSM_Moore[current_state].fptrWaitTransfer();		//wait until transfer is complete
		FSM_Moore[current_state].fptrgetAck();				//receive acknowledge
		current_state = FSM_Moore[current_state].next[0];	//get next state

	}while(HT16K33_I2C_S0 != current_state);

	FSM_Moore[current_state].stop(); //stop transmission
}

void HT16K33_data_transmit()
{
	uint8_t	current_state;
	uint8_t tx_or_rx;
	uint8_t writebyte;

	tx_or_rx = FSM_Moore[HT16K33_I2C_S0].Transmit_Receive;
	current_state = HT16K33_I2C_S0;

	FSM_Moore[HT16K33_I2C_S0].fptrTxRx(tx_or_rx); //Enable transmission
	FSM_Moore[HT16K33_I2C_S0].start();

	writebyte = FSM_Moore[HT16K33_I2C_S0].writebyte;		//Retrieve current writebyte value
	FSM_Moore[HT16K33_I2C_S0].fptrWrite(writebyte);		//Send writebyte current value
	FSM_Moore[HT16K33_I2C_S0].fptrWaitTransfer();		//wait until transfer is complete

	writebyte = FSM_Moore[HT16K33_I2C_S4].writebyte;		//Retrieve current writebyte value
	FSM_Moore[HT16K33_I2C_S4].fptrWrite(writebyte);		//Send writebyte current value
	FSM_Moore[HT16K33_I2C_S4].fptrWaitTransfer();		//wait until transfer is complete
	FSM_Moore[HT16K33_I2C_S4].fptrgetAck();				//receive acknowledge

	do
	{
		writebyte = *FSM_Display1[current_state].writebyte;		//Retrieve current writebyte value
		FSM_Display1[current_state].fptrWrite(writebyte);		//Send writebyte current value
		FSM_Display1[current_state].fptrWaitTransfer();		    //wait until transfer is complete
		FSM_Display1[current_state].fptrgetAck();				//receive acknowledge

		writebyte = *FSM_Display2[current_state].writebyte;		//Retrieve current writebyte value
		FSM_Display2[current_state].fptrWrite(writebyte);	 	//Send writebyte current value
		FSM_Display2[current_state].fptrWaitTransfer();		    //wait until transfer is complete
		FSM_Display2[current_state].fptrgetAck();				//receive acknowledge
		current_state = FSM_Display2[current_state].next[0];	//get next state

	}while(HT16K33_I2C_S0 != current_state);

	FSM_Moore[HT16K33_I2C_S0].stop();
}

void HT16K33_set_txt(uint8_t txt_symbol, uint8_t ndisplay)
{
	//look up for text symbol in table
	switch(ndisplay)
	{
		case FIRST_DISPLAY:
		 		/** look up for text symbol in table and update global matrix **/
				HT16K33_get_sprite_data(txt_symbol, FIRST_DISPLAY);
				/** Show global matrix on first LCD display global matrix **/
				HT16K33_data_transmit();
		break;
		case SECOND_DISPLAY:
				/** look up for text symbol in table and update global matrix **/
			    HT16K33_get_sprite_data(txt_symbol, SECOND_DISPLAY);
				/** Show global matrix on second LCD display global matrix **/
				HT16K33_data_transmit();
		break;
		default:
		break;
	}
}

void HT16K33_get_sprite_data(uint8_t value, uint8_t ndisplay)
{
    uint8_t i;
    uint8_t index;
    boolean_t value_found_flag;

    value_found_flag = 0;

    for(i = 0; TIME_HT16K33_TABLE_SIZE > i ; i++)
    {
		/** Verify if the value given corresponds to any data on the table **/
        if(display_info[i].value == value)
        {
            index = i; //set the index corresponding to the value
            value_found_flag = TRUE; //indicate that a value has been found
            break; //end loop
        }
        else
        {
            continue; //do-nothing
        }
    }

    /** If the index is valid, it returns the display information **/
    if(TRUE == value_found_flag)
    {
		/** Set the rows corresponding to the value found on the table **/
		switch(ndisplay)
		{
			case FIRST_DISPLAY:
				global_matrix.led_display_1[row_0] = display_info[index].row_0;
				global_matrix.led_display_1[row_1] = display_info[index].row_1;
				global_matrix.led_display_1[row_2] = display_info[index].row_2;
				global_matrix.led_display_1[row_3] = display_info[index].row_3;
				global_matrix.led_display_1[row_4] = display_info[index].row_4;
				global_matrix.led_display_1[row_5] = display_info[index].row_5;
				global_matrix.led_display_1[row_6] = display_info[index].row_6;
				global_matrix.led_display_1[row_7] = display_info[index].row_7;
			break;
			case SECOND_DISPLAY:
				global_matrix.led_display_2[row_0] = display_info[index].row_0;
				global_matrix.led_display_2[row_1] = display_info[index].row_1;
				global_matrix.led_display_2[row_2] = display_info[index].row_2;
				global_matrix.led_display_2[row_3] = display_info[index].row_3;
				global_matrix.led_display_2[row_4] = display_info[index].row_4;
				global_matrix.led_display_2[row_5] = display_info[index].row_5;
				global_matrix.led_display_2[row_6] = display_info[index].row_6;
				global_matrix.led_display_2[row_7] = display_info[index].row_7;
			break;
			default:
			break;
		}
    }
}

void HT16K33_DOT(void)
{
	I2C_tx_rx_mode(I2C_TX);
	I2C_start();
	I2C_write_byte(HT16K33_WRITE_CONTROL);
	I2C_wait();

	I2C_write_byte(HT16K33_ADDRESS);
	I2C_wait();
	I2C_get_ack();

	I2C_write_byte(HT16K33_DOT_MASK);
	I2C_wait();
	I2C_get_ack();

	I2C_stop();
}

void HT16K33_STARTUP()
{
	global_matrix.led_display_1[row_0] = display_startup[row_0].row_0;
	global_matrix.led_display_1[row_1] = display_startup[row_0].row_1;
	global_matrix.led_display_1[row_2] = display_startup[row_0].row_2;
	global_matrix.led_display_1[row_3] = display_startup[row_0].row_3;
	global_matrix.led_display_1[row_4] = display_startup[row_0].row_4;
	global_matrix.led_display_1[row_5] = display_startup[row_0].row_5;
	global_matrix.led_display_1[row_6] = display_startup[row_0].row_6;
	global_matrix.led_display_1[row_7] = display_startup[row_0].row_7;

	global_matrix.led_display_2[row_0] = display_startup[row_0].row_0;
	global_matrix.led_display_2[row_1] = display_startup[row_0].row_1;
	global_matrix.led_display_2[row_2] = display_startup[row_0].row_2;
	global_matrix.led_display_2[row_3] = display_startup[row_0].row_3;
	global_matrix.led_display_2[row_4] = display_startup[row_0].row_4;
	global_matrix.led_display_2[row_5] = display_startup[row_0].row_5;
	global_matrix.led_display_2[row_6] = display_startup[row_0].row_6;
	global_matrix.led_display_2[row_7] = display_startup[row_0].row_7;

	HT16K33_data_transmit();
}

