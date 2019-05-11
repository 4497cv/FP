/*
 * Bits.h
 *
 *  Created on: 04/09/2018
 *      Author: jlpe
 */

#ifndef BITS_H_
#define BITS_H_

#define NULL 0
#define ZERO 0

/*! This definition is as a general definitions to bits in regiter or pins in the microcontroller.*/
typedef enum 
{
	bit_0,  /*!< Bit 0 */
	bit_1,  /*!< Bit 1 */
	bit_2,  /*!< Bit 2 */
	bit_3,  /*!< Bit 3 */
	bit_4,  /*!< Bit 4 */
	bit_5,  /*!< Bit 5 */
	bit_6,  /*!< Bit 6 */
	bit_7,  /*!< Bit 7 */
	bit_8,  /*!< Bit 8 */
	bit_9,  /*!< Bit 9 */
	bit_10, /*!< Bit 10 */
	bit_11, /*!< Bit 11 */
	bit_12, /*!< Bit 12 */
	bit_13, /*!< Bit 13 */
	bit_14, /*!< Bit 14 */
	bit_15, /*!< Bit 15 */
	bit_16, /*!< Bit 16 */
	bit_17, /*!< Bit 17 */
	bit_18, /*!< Bit 18 */
	bit_19, /*!< Bit 19 */
	bit_20, /*!< Bit 20 */
	bit_21, /*!< Bit 21 */
	bit_22, /*!< Bit 22 */
	bit_23, /*!< Bit 23 */
	bit_24, /*!< Bit 24 */
	bit_25, /*!< Bit 25 */
	bit_26, /*!< Bit 26 */
	bit_27, /*!< Bit 27 */
	bit_28, /*!< Bit 28 */
	bit_29, /*!< Bit 29 */
	bit_30, /*!< Bit 30 */
	bit_31  /*!< Bit 31 */
} BitsType;


typedef enum
{
	buffer_S1,
	buffer_S2,
	buffer_S3,
	buffer_S4,
	buffer_S5,
	buffer_S6,
	buffer_S7,
	buffer_S8
} NoteBuffer_t;

typedef enum
{
	S1,
	S2,
	S3,
	S4,
	S5,
	S6,
	S7,
	S8,
	S9,
	S10,
	S11,
	S12,
	S13
} states_t;

typedef enum
{
	SEQUENCE_ZERO,
	SEQUENCE_ONE,
	SEQUENCE_TWO,
	SEQUENCE_THREE,
	SEQUENCE_FOUR,
	SEQUENCE_FIVE,
	SEQUENCE_SIX,
	SEQUENCE_SEVEN
} sequence_enum_t;


typedef enum
{
	terminal_start,
	terminal_menu,
	terminal_op1,
	terminal_op2,
	terminal_op3,
	terminal_op4
} terminal_state_t;

typedef enum
{
	terminal_S0,
	terminal_S1,
	terminal_S2,
	terminal_S3,
	terminal_S4,
	terminal_S5,
	terminal_S6,
	terminal_S7,
	terminal_S8,
	terminal_S9,
} terminal_config_state_t;

typedef enum
{
	system_Menu,
	system_ClassicMode,
	system_PlayerBoard,
} system_state_t;

typedef enum
{
	ASCII_ENTER = 13,
	ASCII_ESC = 27,
	ASCII_SPACE = 29,
	/**/
	ASCII_LETTER_A = 65,
	ASCII_LETTER_B = 66,
	ASCII_LETTER_C = 67,
	ASCII_LETTER_D = 68,
	ASCII_LETTER_E = 69,
	ASCII_LETTER_F = 70,
	ASCII_LETTER_a = 97,
	ASCII_LETTER_b = 98,
	ASCII_LETTER_c = 99,
	ASCII_LETTER_d = 100,
	ASCII_LETTER_e = 101,
	ASCII_LETTER_f = 102,
	/**/
	ASCII_ONE = 49,
	ASCII_TWO = 50,
	ASCII_THREE = 51,
	ASCII_FOUR = 52,
	ASCII_FIVE = 53,
	ASCII_SIX = 54,
	ASCII_SEVEN = 55,
	ASCII_EIGHT = 56,
	ASCII_NINE = 57,
	ASCII_ZERO = 48,
	/**/
	ASCII_TIME_FORM = 58,
	ASCII_DATE_FORM = 47,
	ASCII_STOP = 59,
	ASCII_DOT = 250
}ASCII_type;

typedef enum
{
	C = 67,
	D = 68,
	E = 69,
	F = 70,
	G = 71,
	A = 65,
	B = 66,
} musical_notes;
/** This enumeration defines the UART's ports to be used **/
typedef enum {UART_0,UART_1,UART_2,UART_3,UART_4,UART_5} uart_channel_t;

typedef enum{FALSE, TRUE} boolean_t;

/*! This definition is as a general definitions to bits turn-on or turn-off any bit*/
typedef enum {BIT_OFF, BIT_ON} BIT_ON_OFF_Type;

#endif /* BITS_H_ */
