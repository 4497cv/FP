/*!
	\file 	  eeprom.c
	\brief    This is the source file for the EEPROM module. It contains functions
			  for the operation of the EEPROM integrated circuit.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez, ie705694
	\date	  10/05/2019
*/

#include "eeprom.h"

static uint8_t eeprom_storage[EEPROM_BYTES] = {0}; //four users 32 bytes in total; 8 bytes per user.
static boolean_t user_available[4] = {FALSE};
static uint8_t buffer[7] = {0};
static uint8_t High_Address_g;
static uint8_t Low_Address_g;
static uint8_t data_g;
static uint8_t write_control = (0xA0);
static uint8_t read_control = (EEPROM_READ_CONTROL);

static const EEPROM_state_t FSM_EEPROM_WR[4]=
{
	{I2C_TX,   	 &write_control,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S0}}, //WRITE CONTROL STATE
    {I2C_TX,    &High_Address_g,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S0, EEPROM_I2C_S1}}, //SET ADDRESS STATE
	{I2C_TX,     &Low_Address_g,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S3, EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2}}, //WRITE DATA STATE
	{I2C_TX,  		    &data_g,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3}} //WRITE DATA STATE
};

static const EEPROM_state_t FSM_EEPROM_RD[4]=
{
	{I2C_TX,   	 &write_control,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S0}}, //WRITE CONTROL STATE
    {I2C_TX,    &High_Address_g,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S0, EEPROM_I2C_S1}}, //SET ADDRESS STATE
	{I2C_TX,     &Low_Address_g,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S3, EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2}}, //WRITE DATA STATE
	{I2C_TX,  	  &read_control,  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3}} //WRITE DATA STATE
};

static EEPROM_state_t FSM_EEPROM_BUFFER[EBUFFER_SIZE]=
{
    {I2C_TX,   &buffer[0],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S4, EEPROM_I2C_S5, EEPROM_I2C_S6, EEPROM_I2C_S0, EEPROM_I2C_S1}},
	{I2C_TX,   &buffer[1],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S4, EEPROM_I2C_S5, EEPROM_I2C_S6, EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2}},
	{I2C_TX,   &buffer[2],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S3, EEPROM_I2C_S4, EEPROM_I2C_S5, EEPROM_I2C_S6, EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3}},
	{I2C_TX,   &buffer[3],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S4, EEPROM_I2C_S5, EEPROM_I2C_S6, EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S4}},
	{I2C_TX,   &buffer[4],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S5, EEPROM_I2C_S6, EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S4, EEPROM_I2C_S5}},
	{I2C_TX,   &buffer[5],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S6, EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S4, EEPROM_I2C_S5, EEPROM_I2C_S6}},
	{I2C_TX,   &buffer[6],  I2C_tx_rx_mode, I2C_write_byte, I2C_wait, I2C_get_ack, I2C_start, I2C_stop,  {EEPROM_I2C_S0, EEPROM_I2C_S1, EEPROM_I2C_S2, EEPROM_I2C_S3, EEPROM_I2C_S4, EEPROM_I2C_S5, EEPROM_I2C_S6, EEPROM_I2C_S7}},
};

void EEPROM_write_mem(uint16_t address, uint8_t data)
{
	uint8_t	current_state;
	uint8_t tx_or_rx;
	uint8_t writebyte;

	/*set high address*/
	High_Address_g = (address >> bit_8);
	/*set low address*/
	Low_Address_g =  address;
	/* set data */
	data_g = data;

	current_state = EEPROM_I2C_S0;

	tx_or_rx = FSM_EEPROM_WR[current_state].Transmit_Receive;
	FSM_EEPROM_WR[current_state].fptrTxRx(tx_or_rx); //Enable transmission
	FSM_EEPROM_WR[current_state].start();

	do
	{
		writebyte = *FSM_EEPROM_WR[current_state].writebyte;		//Retrieve current writebyte value
		FSM_EEPROM_WR[current_state].fptrWrite(writebyte);		//Send writebyte current value
		FSM_EEPROM_WR[current_state].fptrWaitTransfer();		//wait until transfer is complete
		FSM_EEPROM_WR[current_state].fptrgetAck();				//receive acknowledge
		current_state = FSM_EEPROM_WR[current_state].next[0];	//get next state
	}while(EEPROM_I2C_S0 != current_state);

	FSM_EEPROM_WR[current_state].stop(); //stop transmission
}

int8_t EEPROM_read_mem(uint16_t address)
{
	uint8_t	current_state;
	uint8_t tx_or_rx;
	uint8_t writebyte;
	uint8_t data;

	/*set high address*/
	High_Address_g = (address >> bit_8);
	/*set low address*/
	Low_Address_g =  address;

	current_state = EEPROM_I2C_S0;

	tx_or_rx = FSM_EEPROM_RD[current_state].Transmit_Receive;
	FSM_EEPROM_RD[current_state].fptrTxRx(tx_or_rx); //Enable transmission
	FSM_EEPROM_RD[current_state].start();

	do
	{
		writebyte = *FSM_EEPROM_RD[current_state].writebyte;		//Retrieve current writebyte value
		FSM_EEPROM_RD[current_state].fptrWrite(writebyte);		//Send writebyte current value
		FSM_EEPROM_RD[current_state].fptrWaitTransfer();		//wait until transfer is complete
		FSM_EEPROM_RD[current_state].fptrgetAck();				//receive acknowledge
		current_state = FSM_EEPROM_RD[current_state].next[0];	//get next state
	}while(EEPROM_I2C_S0 != current_state);

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_nack();

	FSM_EEPROM_RD[current_state].stop(); //stop transmission

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();

	return (data);
}

void EEPROM_read_mem_page(void)
{
	int8_t data;
	uint8_t address = 0;

	/*Need to separate address to High and Low address*/
	/*high address*/
	uint8_t Haddr = address >> bit_8;
	/*low address*/
	uint8_t Laddr = address;

	/*Change I2C module to Tx mode*/
	I2C_tx_rx_mode(I2C_TX);
	/*Start bit*/
	I2C_start();
	/*Send the RTC Address to the register*/
	I2C_write_byte(EEPROM_WRITE_CONTROL); /*1010/Direccion fisica(A2/A1/A0)*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();
	/*delay*/
	EEPROM_delay(EEPROM_DELAY);

	/*Register address*/
	I2C_write_byte(Haddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();
	/*delay*/
	EEPROM_delay(EEPROM_DELAY);

	/*Register address*/
	I2C_write_byte(Laddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();
	/*delay*/
	EEPROM_delay(EEPROM_DELAY);

	/*Send the start bit signal again so we can send now the data to read*/
	I2C_repeated_start();

	/*Send the RTC Address to the register*/
	I2C_write_byte(EEPROM_READ_CONTROL); /*1010/Direccion fisica(A2/A1/A0)*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();
	/*delay*/
	EEPROM_delay(EEPROM_DELAY);

	/*Change I2C module to Rx mode*/
	I2C_tx_rx_mode(I2C_RX);

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_get_ack();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	buffer[0] = data;

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_get_ack();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	buffer[1] = data;

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_get_ack();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	buffer[2] = data;

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_get_ack();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	buffer[3] = data;

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_get_ack();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	buffer[4] = data;

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_get_ack();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	buffer[5] = data;

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_nack();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	buffer[6] = data;

	EEPROM_delay(EEPROM_DELAY);

	/*Send the stop signal*/
	I2C_stop();
}

void EEPROM_clear_mem()
{
	uint8_t i;

	for(i = FALSE; EEPROM_SIZE > i; i++)
	{
		EEPROM_write_mem(i, CLEAR);
	}
}

void EEPROM_delay(uint32_t delay){
	uint32_t i;
	
	i = delay;

	while(i!=0)
	{
		i--;
	}
}

void eeprom_store_record(uint8_t username[3], uint8_t time_g)
{	
	uint8_t index;
	uint8_t index_user_addr[NUM_USERS] = {0};
	float min_fp;
	uint8_t min;
	uint8_t sec;

	min_fp = time_g/60;
	min = (uint8_t) min_fp;

	if(ZERO == min)
	{
		sec = time_g;
	}
	else if(ONE == min)
	{
		sec = time_g - (ONE * MINUTE);
	}
	else if(TWO == min)
	{
		sec = time_g - (TWO * MINUTE);
	}
	else
	{

	}

#ifndef DEBUG
	printf("time:0%i:0%i  Username: %c %c %c \n", min, sec, username[0], username[1], username[2]);
#endif

	update_userspace_information();

	index = get_available_userspace();
	index = index*6;

	/*Store in buffer and eeprom user is writen*/
	eeprom_storage[index] = ONE;
	EEPROM_write_mem(index, ONE);
	index++;
	delay(65000);
	/*Store in buffer and eeprom the user tag*/
	eeprom_storage[index] = username[ZERO];
	EEPROM_write_mem(index, username[ZERO]);
	index++;
	delay(65000);
	eeprom_storage[index] = username[ONE];
	EEPROM_write_mem(index, username[ONE]);
	index++;
	delay(65000);
	eeprom_storage[index] = username[TWO];
	EEPROM_write_mem(index, username[TWO]);
	index++;
	delay(65000);
	/*Store in buffer and eeprom the score time*/
	eeprom_storage[index] = min;
	EEPROM_write_mem(index, min);
	index++;
	delay(65000);
	eeprom_storage[index] = sec;
	EEPROM_write_mem(index, sec);
	delay(65000);

	/*rst index*/
	index = 0;

}


void update_userspace_information(void)
{
	uint8_t i;
	uint8_t index;

	index = 0;

	for(i=0; NUM_USERS*6 > i; i+=6)
	{
		if(ZERO == eeprom_storage[i])
		{
			user_available[index] = TRUE;
		}
		else
		{
			user_available[index] = FALSE;
		}
		index++;
	}
}

uint8_t get_available_userspace(void)
{
	uint8_t i;

	for(i = ZERO; NUM_USERS > i; i++)
	{
		if(TRUE == user_available[i])
		{
			break;
		}
	}

	return i;
}

void eeprom_read_record()
{
	uint8_t index_read_t = 0;

	/*Read EEPROM*/
	delay(400);
	EEPROM_read_mem(2);
	index_read_t++;
	delay(400);
	EEPROM_read_mem(index_read_t);
	index_read_t++;
	delay(400);
	EEPROM_read_mem(index_read_t);
	index_read_t++;
	delay(400);
	EEPROM_read_mem(index_read_t);
	index_read_t++;
	delay(400);
	EEPROM_read_mem(index_read_t);

	/*rst index*/
	index_read_t = 0;
}

uint8_t get_buffer(uint8_t index)
{
	return buffer[index];
}
