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

void EEPROM_write_mem(uint16_t address, uint8_t data)
{
	/*Need to separate address to High and Low address*/
	/*high address*/
	uint8_t Haddr = address >> bit_8;
	/*low address*/
	uint8_t Laddr =  address;

	/*Set as Tx*/
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
	//EEPROM_delay(EEPROM_DELAY);

	/*Register address*/
	I2C_write_byte(Haddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();
	/*delay*/
	//EEPROM_delay(EEPROM_DELAY);

	/*Register address*/
	I2C_write_byte(Laddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();
	/*delay*/
	//EEPROM_delay(EEPROM_DELAY);

	/*Register address*/
	I2C_write_byte(data); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();
	/*delay*/
	//EEPROM_delay(EEPROM_DELAY);

	/*Send the stop signal*/
	I2C_stop();

	//I2C_repeated_start();
}

int8_t EEPROM_read_mem(uint16_t address)
{
	int8_t data;
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
	I2C_nack();
	/*delay*/
	EEPROM_delay(EEPROM_DELAY);

	/*Send the stop signal*/
	I2C_stop();

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
	float sec_fp;
	uint8_t min;
	uint8_t sec;

	min_fp = time_g/60;
	min = (uint8_t) min_fp;

	if(ZERO == min)
	{
		sec = time_g;
	}
	else
	{
		sec_fp = (min_fp - min) * 100;
		sec = (uint8_t) sec_fp;
	}

#ifndef DEBUG
	printf("time:0%i:0%i  Username: %c %c %c \n", min, sec, username[0], username[1], username[2]);
#endif

	update_userspace_information();

	index = get_available_userspace();
	index = index*6;

	/*Store in buffer and eeprom user is writen*/
	eeprom_storage[index] = 1;
	EEPROM_write_mem(index, 1);
	index++;
	delay(65000);
	/*Store in buffer and eeprom the user tag*/
	eeprom_storage[index] = username[0];
	EEPROM_write_mem(index, username[0]);
	index++;
	delay(65000);
	eeprom_storage[index] = username[1];
	EEPROM_write_mem(index, username[1]);
	index++;
	delay(65000);
	eeprom_storage[index] = username[2];
	EEPROM_write_mem(index, username[2]);
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

	EEPROM_read_mem_page();

	return buffer[index];
}
