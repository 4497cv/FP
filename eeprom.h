/*!
	\file 	  eeprom.h
	\brief
			  This is the header file for the EEPROM module. It contains functions
			  for the operation of the EEPROM integrated circuit.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez,ie705694
	\date	  10/05/2019
*/

#ifndef EEPROM_H_
#define EEPROM_H_

#include "bits.h"
#include "I2C.h"

#define CLEAR 0x0000

#define EEPROM_WRITE_CONTROL 0xAE
#define EEPROM_READ_CONTROL 0xAF

#define EEPROM_SIZE 0x00FF

#define PAGE_SIZE 0x64

#define EEPROM_DELAY 1000

typedef struct
{
	uint8_t Transmit_Receive;
	uint8_t writebyte;
	void(*fptrTxRx)(uint8_t tx_or_rx);
	void (*fptrWrite)(uint8_t data);
	void (*fptrWaitTransfer)(void);
	void (*fptrgetAck)(void);
	void (*start)(void);
	void (*stop)(void);
	uint8_t next[4];
} EEPROM_state_t;


/*\brief Funct to write in the address wirtten in the param via I2C
 *\param[add] Address
 *\param[data] data to store
 * */
void EEPROM_write_mem(uint16_t address, uint8_t data);

/*\brief Funct to write in the address wirtten in the param via I2C
 *\param[add] Address
 *\param[data] data to store
 * */
void EEPROM_write_string_mem(uint16_t address,int8_t* ptr_data);

/*\brief Funct to read the address wirtten in the param via I2C
 *\param[add] Address
 * */
int8_t EEPROM_read_mem(uint16_t address);

/*\brief Funct to read the address wirtten in the param via I2C
 *\param[add] Address
 * */
int8_t* EEPROM_read_string_mem(uint16_t address);

/*\brief Funct to clear the mem
 * */
void EEPROM_clear_mem();

/*\brief Funct to create a delay so we can read the data in the logic analyser
 *\param[add] delay
 * */
void EEPROM_delay(uint32_t delay);

#endif /* EEPROM_H_ */
