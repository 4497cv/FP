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
#include "i2c.h"
#include "stdint.h"
#include "delay.h"

#define CLEAR 0x0000

#define EEPROM_WRITE_CONTROL 0xA0
#define EEPROM_READ_CONTROL 0xA1
#define NUM_USERS 4
#define EEPROM_BYTES 32
#define EEPROM_SIZE 0x00FF
#define EBUFFER_SIZE 7

#define PAGE_SIZE 0x64

#define EEPROM_DELAY 6500

typedef struct
{
	uint8_t Transmit_Receive;
	uint8_t *writebyte;
	void(*fptrTxRx)(uint8_t tx_or_rx);
	void (*fptrWrite)(uint8_t data);
	void (*fptrWaitTransfer)(void);
	void (*fptrgetAck)(void);
	void (*start)(void);
	void (*stop)(void);
	uint8_t next[4];
} EEPROM_state_t;

typedef enum
{
	EEPROM_I2C_S0,
	EEPROM_I2C_S1,
	EEPROM_I2C_S2,
	EEPROM_I2C_S3,
	EEPROM_I2C_S4,
	EEPROM_I2C_S5,
	EEPROM_I2C_S6,
	EEPROM_I2C_S7,
	EEPROM_I2C_S8
} EEPROM_enum_t;

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

/*\brief Funct to read via pag read all the data of the player
 *\param[add] void
 * */
void eeprom_read_record(void);

/*\brief Funct to update if any space was released for the users
 *\param[add] void
 * */
void update_userspace_information(void);

/*\brief Funct used to check if there is a user available
 *\param[add] void
 * */
uint8_t get_available_userspace(void);

/*\brief Funct send the data read from the eeprom to another layer
 *\param[add] index
 * */
uint8_t get_buffer(uint8_t index);

void eeprom_store_record(uint8_t username[3], uint8_t time_g);

#endif /* EEPROM_H_ */
