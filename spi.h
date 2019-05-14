/*!
	@file	  SPI.h

	@brief    This is the header file for the Serial Protocol Interface driver for Kinetis K64.
		  i.e.,this is the application programming interface(API).

	@authors: César Villarreal Hernández, ie707560
		  José Luis Rodríguez Gutierrez,ie705694

	@date	  24/03/2019

	@TODO:    Implement the functions defined below, and write proper comments
		  to each function.
 */

#ifndef SPI_H_
#define SPI_H_
#include <MK64F12.h>
#include "stdint.h"
#include "gpio.h"

/** Constant that represent the clock enable for the SPI modules */
#define SPI0_CLOCK_GATING 0x1000
#define SPI1_CLOCK_GATING 0x2000
#define SPI2_CLOCK_GATING 0x1000

/** Constant to define the frame size in the SPI transmission */
#define SPI_FSIZE_4 SPI_CTAR_FMSZ(3)
#define SPI_FSIZE_5 SPI_CTAR_FMSZ(4)
#define SPI_FSIZE_6 SPI_CTAR_FMSZ(5)
#define SPI_FSIZE_7 SPI_CTAR_FMSZ(6)
#define SPI_FSIZE_8 SPI_CTAR_FMSZ(7)
#define SPI_FSIZE_9 SPI_CTAR_FMSZ(8)
#define SPI_FSIZE_10 SPI_CTAR_FMSZ(9)
#define SPI_FSIZE_11 SPI_CTAR_FMSZ(10)
#define SPI_FSIZE_12 SPI_CTAR_FMSZ(11)
#define SPI_FSIZE_13 SPI_CTAR_FMSZ(12)
#define SPI_FSIZE_14 SPI_CTAR_FMSZ(13)
#define SPI_FSIZE_15 SPI_CTAR_FMSZ(14)
#define SPI_FSIZE_16 SPI_CTAR_FMSZ(15)

/** Constants to double the clock rate */
#define SPI_DOUBLE_BAUD_RATE (1u)
#define SPI_NON_DOUBLE_BAUD_RATE (0u)

/** Constant to configure the baud rate */
#define SPI_BAUD_RATE_2     (0x00u)
#define SPI_BAUD_RATE_4     (0x01u)
#define SPI_BAUD_RATE_6     (0x02u)
#define SPI_BAUD_RATE_8     (0x03u)
#define SPI_BAUD_RATE_16    (0x04u)
#define SPI_BAUD_RATE_32    (0x05u)
#define SPI_BAUD_RATE_64    (0x06u)
#define SPI_BAUD_RATE_128   (0x07u)
#define SPI_BAUD_RATE_256   (0x08u)
#define SPI_BAUD_RATE_512   (0x09u)
#define SPI_BAUD_RATE_1024  (0x0Au)
#define SPI_BAUD_RATE_2048  (0x0Bu)
#define SPI_BAUD_RATE_4096  (0x0Cu)
#define SPI_BAUD_RATE_8192  (0x0Du)

/** Constant that used to select a chip select */
#define SPI_PCSIS_0 (0x100u)
#define SPI_PCSIS_1 (0x200u)
#define SPI_PCSIS_2 (0x400u)
#define SPI_PCSIS_3 (0x800u)
#define SPI_PCSIS_4 (0x1000u)
#define SPI_PCSIS_5 (0x2000u)


/*Type for FIFO configuration*/
typedef enum {SPI_DISABLE_FIFO, SPI_ENABLE_FIFO} spi_enable_fifo_t;
/*Type for polarity configuration*/
typedef enum {SPI_LOW_POLARITY, SPI_HIGH_POLARITY} spi_polarity_t;
/*Type for phase configuration*/
typedef enum {SPI_LOW_PHASE, SPI_HIGH_PHASE} spi_phase_t;
/*Type for the star of the frame, either MSB o LSM */
typedef enum {SPI_MSB, SPI_LSM} spi_lsb_or_msb_t;
/*Type for SPI modules*/
typedef enum
{
	SPI_0,
	SPI_1,
	SPI_2
} spi_channel_t;

/*Type for master or slave configuration*/
typedef enum{SPI_SLAVE, SPI_MASTER} spi_master_t;
/*Type for GPIO configuration that activates the GPIO for SPI*/
typedef struct{
	gpio_port_name_t gpio_port_name;
	uint32_t spi_clk;
	uint32_t spi_sout;
}spi_port_config_t;

/*Type that is used for SPI configuration, It contains all the information needed for a SPI module*/
typedef struct
{
	spi_enable_fifo_t spi_enable_fifo;
	spi_polarity_t spi_polarity;
	spi_phase_t spi_phase;
	spi_lsb_or_msb_t spi_lsb_or_msb;
	spi_channel_t spi_channel;
	spi_master_t spi_master;
	gpio_pin_control_register_t pin_config;
	uint8_t spi_baudrate;
	uint32_t spi_frame_size;
	spi_port_config_t spi_gpio_port;
} spi_config_t;


void SPI_init(const spi_config_t* SPI_Config);
/*!
	@brief      This function enables the clock module of the SPI by modifying
		    the MDIS bits.
	@param[in]  spi_channel_t
	@return     static void
 */
static void SPI_enable(spi_channel_t);

/*!
	@brief      This function activates the clock gating for the SPI.
	@param[in]  spi_channel_t
	@return     static void
 */
static void SPI_clk(spi_channel_t);

/*!
	@brief      This function configures the SPI as a master or slave depending
		    on the value of masterOrslave.
	@param[in]  spi_channel_t
	@param[in]  spi_master_t
	@return     static void
 */
static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave);

/*!
	@brief      This function activates the TX and RX FIFOs of the SPI depending
		    on the value of enableOrdisable.
	@param[in]  spi_channel_t
	@param[in]  spi_enable_fifo_t
	@return     static void
 */
static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable);

/*!
        @brief      This function selects the clock polarity depending on the value of cpol; selects the inactive state
                    of the Serial Communications Clock (SCK).
        @note       For successful communication between serial devices, the devices must have identical clock polarities.
        @param[in]  spi_channel_t
        @param[in]  spi_polarity_t
        @return	    static void
 */
static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol);

/*!
	@brief      This function selects the frame size depending on the value of
		    frameSize and the macros that are defined above.
	@param[in]  spi_channel_t
	@param[in]  uint32_t
	@return	    static void
 */
static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize);

/*!
	@brief      This function selects the clock phase depending on the value of
		    cpha.
	@param[in]  spi_channel_t
	@param[in]  spi_phase_t
	@return	    static void
 */
static void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha);

/*!
	@brief      This function selects the baud rate depending on the value of
		    baudRate and the macros that are defined above.
	@param[in]  spi_channel_t
	@param[in]  uint32_t
	@return	    static void
 */
static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate);

/*!
	@brief     This function selects if MSB or LSM bits is first transmitted.
	@param[in] spi_channel_t
	@param[in] uint32_t
	@return	   static void
 */
static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb);

/*!
	@brief     This function starts the SPI transmission by modifying
		   the value of HALT bit.
	@param[in] spi_channel_t
	@return	   void
 */
void SPI_start_tranference(spi_channel_t channel);

/*!
	@brief     This function stops the SPI transmission by modifying
		   the value of HALT bit.
	@param[in] spi_channel_t
	@return	   void
 */
void SPI_stop_tranference(spi_channel_t channel);

/*!
	@brief     This function transmits the information contained in data.
	@param[in] uint8_t
	@return	   void
 */
void SPI_send_one_byte(uint8_t Data);

 /*!
	@brief     This function configures the SPI for transmission.
	@param[in] pointer to constant (const spi_config_t*)
	@return	   void
  */

#endif /* SPI_H_ */
