/**
	\file 	  matrix.h
	\brief
			  This is the header file for the matrix module. It contains functions
			  for the operation of the M1707042 8*8 LED matrix.
	\authors: César Villarreal Hernández, ie707560
	          José Luis Rodríguez Gutierrez,ie705694
	\date	  10/05/2019
 */

#ifndef HT16K33_H_
#define HT16K33_H_

#include "bits.h"
#include "i2c.h"

#define HT16K33_WRITE_CONTROL 0xE0
#define HT16K33_ADDRESS 		0x00
#define HT16K33_OSC_CONTROL1 0x21
#define HT16K33_OSC_CONTROL2 0x81
#define HT16K33_OSC_CONTROL3 0xEF

#define HT16K33_I2C_S0 0  //WRITE CONTROL STATE
#define HT16K33_I2C_S1 1  //SET ADDRESS STATE
#define HT16K33_I2C_S2 2  //WRITE DATA STATE
#define HT16K33_I2C_S3 3
#define HT16K33_I2C_S4 4  //WRITE CONTROL STATE
#define HT16K33_I2C_S5 5  //SET ADDRESS STATE
#define HT16K33_I2C_S6 6  //WRITE DATA STATE
#define HT16K33_I2C_S7 7
#define HT16K33_I2C_S8 8  //WRITE CONTROL STATE

#define TIME_HT16K33_TABLE_SIZE 60
#define N_ROWS 8

#define HT16K33_DELAY 1000

#define ERSTEN  1
#define ZWEITEN 2
#define SQ_START 0

#define FIRST_DISPLAY 1
#define SECOND_DISPLAY 2

#define HT16K33_DOT_MASK 0x01

typedef struct
{
   uint8_t led_display_1[N_ROWS];
   uint8_t led_display_2[N_ROWS];
} led_HT16K33_t;

typedef struct 
{
	uint8_t value;
	uint8_t led_display[N_ROWS];
} table_HT16K33_t;

typedef enum
{
	row_0,
	row_1,
	row_2,
	row_3,
	row_4,
	row_5,
	row_6,
	row_7
} display_row_t;

typedef struct
{
    uint8_t value;
	uint8_t row_0;
    uint8_t row_1;
    uint8_t row_2;
    uint8_t row_3;
    uint8_t row_4;
	uint8_t row_5;
    uint8_t row_6;
    uint8_t row_7;
}   time_display_t;

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
}I2C_state_t;

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
	uint8_t next[9];
}I2C_D_state_t;



/*!
 	 \brief		 This function configures the initial settings for the MATRIX.
 	 \param[in]  void
 	 \return     void
 */
void HT16K33_init(void);

/*!
 	 \brief		 This function configures the initial settings for the MATRIX.
 	 \param[in]  int8_t
 	 \return     void
 */
void HT16K33_write_mem(int8_t data);


void HT16K33_data_transmit(void);

void HT16K33_set_txt(uint8_t txt_symbol, uint8_t ndisplay);

void HT16K33_set_time(int8_t* txt);

void HT16K33_delay(uint32_t delay);

void HT16K33_get_sprite_data(uint8_t value, uint8_t ndisplay);

void HT16K33_STARTUP(void);

void HT16K33_DOT(void);

void MATRIX_word_transmit(int8_t x[8][8], int8_t y[8][8]);

void MATRIX_set_txt(int8_t* txt);
#endif /* HT16K33_H_ */
