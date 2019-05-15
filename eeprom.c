/*!
	\file 	  eeprom.c
	\brief
			  This is the source file for the EEPROM module. It contains functions
			  for the operation of the EEPROM integrated circuit.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez, ie705694
	\date	  10/05/2019
*/

#include "eeprom.h"

static int8_t mem_data[PAGE_SIZE] = {FALSE};

void EEPROM_write_mem(uint16_t address, uint8_t data)
{
	EEPROM_delay(6500);
	/** Retrieve high address **/
	uint8_t Haddr = address >> bit_8; 
	/** Retrieve low address **/
	uint8_t Laddr =  address;

	/** Enable transmission **/
	I2C_tx_rx_mode(I2C_TX);
	/** Send start signal **/
	I2C_start();

	/*Send the RTC Address to the register*/
	I2C_write_byte(EEPROM_WRITE_CONTROL);
	/*Check if I2C is busy*/
	I2C_wait();
	I2C_get_ack();

	/*Register address*/
	I2C_write_byte(Haddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();


	/*Register address*/
	I2C_write_byte(Laddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();

	/*Register address*/
	I2C_write_byte(data); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();

	/*Send the stop signal*/
	I2C_stop();
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

	/*Register address*/
	I2C_write_byte(Haddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();

	/*Register address*/
	I2C_write_byte(Laddr); /*Address = data*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();

	/*Send the start bit signal again so we can send now the data to read*/
	I2C_repeated_start();

	/*Send the RTC Address to the register*/
	I2C_write_byte(EEPROM_READ_CONTROL); /*1010/Direccion fisica(A2/A1/A0)*/
	/*Check if I2C is busy*/
	I2C_wait();
	/*Recevie the Acknowledge*/
	I2C_get_ack();

	/*Change I2C module to Rx mode*/
	I2C_tx_rx_mode(I2C_RX);

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();
	/*Check if I2C is busy*/
	I2C_wait();
	/*Generate ~Acknowledge*/
	I2C_nack();

	/*Send the stop signal*/
	I2C_stop();

	/*data get the value that's in the I2C_D register*/
	data = I2C_read_byte();

	return (data);
}
int8_t* EEPROM_read_string_mem(uint16_t address)
{
	uint8_t counter = FALSE;
	/*Need to separate address to High and Low address*/
	/*high address*/
	uint8_t Haddr = FALSE;
	/*low address*/
	uint8_t Laddr = FALSE;

	do
	{
		Haddr = address >> bit_8;
		Laddr = address;

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

		EEPROM_delay(EEPROM_DELAY);

		/*Register address*/
		I2C_write_byte(Haddr); /*Address = data*/
		/*Check if I2C is busy*/
		I2C_wait();
		/*Recevie the Acknowledge*/
		I2C_get_ack();

		EEPROM_delay(EEPROM_DELAY);

		/*Register address*/
		I2C_write_byte(Laddr); /*Address = data*/
		/*Check if I2C is busy*/
		I2C_wait();
		/*Recevie the Acknowledge*/
		I2C_get_ack();

		EEPROM_delay(EEPROM_DELAY);

		/*Send the start bit signal again so we can send now the data to read*/
		I2C_repeted_start();

		/*Send the RTC Address to the register*/
		I2C_write_byte(EEPROM_READ_CONTROL); /*1010/Direccion fisica(A2/A1/A0)*/
		/*Check if I2C is busy*/
		I2C_wait();
		/*Recevie the Acknowledge*/
		I2C_get_ack();

		EEPROM_delay(EEPROM_DELAY);

		/*Change I2C module to Rx mode*/
		I2C_tx_rx_mode(I2C_RX);

		/*data get the value that's in the I2C_D register*/
		mem_data[counter] = I2C_read_byte();
		/*Check if I2C is busy*/
		I2C_wait();
		/*Generate ~Acknowledge*/
		I2C_nack();

		/*Send the stop signal*/
		I2C_stop();

		/*data get the value that's in the I2C_D register*/
		mem_data[counter] = I2C_read_byte();

		/*Check if the next character stored if null
		 * if so, modify the counter to finish the loop*/
		if(NULL == mem_data[counter])
			counter = PAGE_SIZE;

		/*Increments to the next address*/
		address++;
		/*Increments to the next ptr of the array*/
		counter++;

	}while(counter < PAGE_SIZE);

	return mem_data;
}

void EEPROM_clear_mem()
{
	uint8_t clear;
	for(clear = FALSE;clear<EEPROM_SIZE; clear++)
	{
		EEPROM_write_mem(clear,CLEAR);
	}
}

void EEPROM_delay(uint32_t delay){
	uint32_t i=delay;
	while(i!=0){
		i--;
	}
}
