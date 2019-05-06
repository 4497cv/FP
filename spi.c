/*!
	@file	  spi.c
	@brief    This is the source file for the Serial Protocol Interface driver for Kinetis K64.
		  i.e.,this is the application programming interface(API).
	@authors: César Villarreal Hernández, ie707560
		  José Luis Rodríguez Gutierrez,ie705694
	@date	  24/03/2019
	@TODO:    Implement the functions defined below, and write proper comments
		  to each function.
 */

#include "spi.h"

/*!
	@brief      This function enables the clock module of the SPI by modifying
		    the MDIS bits.
	@param[in]  spi_channel_t
	@return     static void
 */
static void SPI_enable(spi_channel_t channel)
{
  switch(channel)
  {
    case SPI_0:
      /*Enable the module clocks for the SPIO0*/
      SPI0->MCR &= ~(SPI_MCR_MDIS_MASK);
    break;
    case SPI_1:
      /*Enable the module clocks for the SPIO1*/
      SPI1->MCR &= ~(SPI_MCR_MDIS_MASK);
    break;
    case SPI_2:
      /*Enable the module clocks for the SPIO2*/
      SPI2->MCR &= ~(SPI_MCR_MDIS_MASK);
    break;
    default:
    break;
  }
}

/*!
	@brief      This function activates the clock gating for the SPI.
	@param[in]  spi_channel_t
	@return     static void
 */
static void SPI_clk(spi_channel_t channel)
{
  switch(channel)
  {
    case SPI_0:
      /*Activating clock gate to the SPI0 module*/
      SIM->SCGC6 |= SIM_SCGC6_SPI0_MASK;
    break;
    case SPI_1:
      /*Activating clock gate to the SPI1 module*/
      SIM->SCGC6 |= SIM_SCGC6_SPI1_MASK;
    break;
    case SPI_2:
      /*Activating clock gate to the SPI2 module*/
      SIM->SCGC3 |= SIM_SCGC3_SPI2_MASK;
    break;
    default:
    break;
  }
}


/*!
	@brief      This function configures the SPI as a master or slave depending
		    on the value of masterOrslave.
	@param[in]  spi_channel_t
	@param[in]  spi_master_t
	@return     static void
 */
static void SPI_set_master(spi_channel_t channel, spi_master_t masterOrSlave)
{
		switch (channel)
	{
	case SPI_0:
		if(SPI_SLAVE == masterOrSlave)
			SPI0->MCR &= ~(SPI_MCR_MSTR_MASK);
		else if(SPI_MASTER == masterOrSlave)
			SPI0->MCR |= (SPI_MCR_MSTR_MASK);
		break;
	case SPI_1:
		if (SPI_SLAVE == masterOrSlave)
			SPI1->MCR &= ~(SPI_MCR_MSTR_MASK);
		else if(SPI_MASTER == masterOrSlave)
			SPI1->MCR |= (SPI_MCR_MSTR_MASK);
		break;
	case SPI_2:
		if (SPI_SLAVE == masterOrSlave)
			SPI2->MCR &= ~(SPI_MCR_MSTR_MASK);
		else if(SPI_MASTER == masterOrSlave)
			SPI2->MCR |= (SPI_MCR_MSTR_MASK);
		break;
	default:
		break;
	}
}

/*!
	@brief      This function activates the TX and RX FIFOs of the SPI depending
		    on the value of enableOrdisable.
	@param[in]  spi_channel_t
	@param[in]  spi_enable_fifo_t
	@return     static void
 */
static void SPI_fifo(spi_channel_t channel, spi_enable_fifo_t enableOrDisable)
{
		switch (channel)
	{
	case SPI_0:
		if(SPI_DISABLE_FIFO == enableOrDisable)
		{
			SPI0->MCR |= (SPI_MCR_DIS_RXF_MASK);
			SPI0->MCR |= (SPI_MCR_DIS_TXF_MASK);
		}
		else if(SPI_ENABLE_FIFO == enableOrDisable)
		{
			SPI0->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI0->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
		}
		break;
	case SPI_1:
		if (SPI_DISABLE_FIFO == enableOrDisable) {
			SPI1->MCR |= (SPI_MCR_DIS_RXF_MASK);
			SPI1->MCR |= (SPI_MCR_DIS_TXF_MASK);
		} else if (SPI_ENABLE_FIFO == enableOrDisable) {
			SPI1->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI1->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
		}
		break;
	case SPI_2:
		if (SPI_DISABLE_FIFO == enableOrDisable) {
			SPI2->MCR |= (SPI_MCR_DIS_RXF_MASK);
			SPI2->MCR |= (SPI_MCR_DIS_TXF_MASK);
		} else if (SPI_ENABLE_FIFO == enableOrDisable) {
			SPI2->MCR &= ~(SPI_MCR_DIS_RXF_MASK);
			SPI2->MCR &= ~(SPI_MCR_DIS_TXF_MASK);
		}
		break;
	default:
		break;
	}
}

/*!
	@brief      This function selects the clock polarity depending on the
		    value of cpol.
	@param[in]  spi_channel_t
	@param[in]  spi_polarity_t
	@return     static void
 */

/*!
        @brief      This function selects the clock polarity depending on the value of cpol; selects the inactive state
                    of the Serial Communications Clock (SCK).
        @note       For successful communication between serial devices, the devices must have identical clock polarities.
        @param[in]  spi_channel_t
        @param[in]  spi_polarity_t
        @return	    static void
 */
static void SPI_clock_polarity(spi_channel_t channel, spi_polarity_t cpol)
{
  switch(channel)
  {
    case SPI_0:
      if (SPI_HIGH_POLARITY == cpol)
      {
          /** The inactive state value of SCK is high **/
          SPI0->CTAR[0] |= (SPI_CTAR_CPOL_MASK);
      }
      else
      {
          /** The inactive state value of SCK is low **/
			    SPI0->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
      }
    break;
    case SPI_1:
      if (SPI_HIGH_POLARITY == cpol)
      {
          SPI1->CTAR[0] |= (SPI_CTAR_CPOL_MASK);
      }
      else
      {
          SPI1->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
      }
    break;
    case SPI_2:
      if (SPI_HIGH_POLARITY == cpol)
      {
          SPI2->CTAR[0] |= (SPI_CTAR_CPOL_MASK);
      }
      else
      {
          SPI2->CTAR[0] &= ~(SPI_CTAR_CPOL_MASK);
      }
    break;
    default:
    break;
  }
}

/*!
	@brief      This function selects the frame size depending on the value of
		    frameSize and the macros that are defined above.
	@param[in]  spi_channel_t
	@param[in]  uint32_t
	@return	    static void
 */
static void SPI_frame_size(spi_channel_t channel, uint32_t frameSize)
{
	/*FMSZ 16bits*/
	switch(channel)
	{
	case SPI_0:
		SPI0->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI0->CTAR[0] |= frameSize;
		break;
	case SPI_1:
		SPI1->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI1->CTAR[0] |= frameSize;
		break;
	case SPI_2:
		SPI2->CTAR[0] &= ~(SPI_CTAR_FMSZ_MASK);
		SPI2->CTAR[0] |= frameSize;
		break;
	default:
		break;
	}
}

/*!
	@brief      This function selects the clock phase depending on the value of
		    cpha.
	@param[in]  spi_channel_t
	@param[in]  spi_phase_t
	@return	    static void
 */
static void SPI_clock_phase(spi_channel_t channel, spi_phase_t cpha)
{
		switch (channel)
	{
		case SPI_0:
			if (SPI_LOW_PHASE == cpha)
				SPI0->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			else if (SPI_HIGH_PHASE == cpha)
				SPI0->CTAR[0] |= (SPI_CTAR_CPHA_MASK);
			break;
		case SPI_1:
			if (SPI_LOW_PHASE == cpha)
				SPI1->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			else if (SPI_HIGH_PHASE == cpha)
				SPI1->CTAR[0] |= (SPI_CTAR_CPHA_MASK);
			break;
		case SPI_2:
			if (SPI_LOW_PHASE == cpha)
				SPI2->CTAR[0] &= ~(SPI_CTAR_CPHA_MASK);
			else if (SPI_HIGH_PHASE == cpha)
				SPI2->CTAR[0] |= (SPI_CTAR_CPHA_MASK);
			break;
		default:
			break;
	}
}

/*!
	@brief      This function selects the baud rate depending on the value of
		    baudRate and the macros that are defined above.
	@param[in]  spi_channel_t
	@param[in]  uint32_t
	@return	    static void
 */
static void SPI_baud_rate(spi_channel_t channel, uint32_t baudRate)
{
		switch(channel)
	{
			case SPI_0:
				SPI0->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
				SPI0->CTAR[0] |= baudRate;
				break;
			case SPI_1:
				SPI1->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
				SPI1->CTAR[0] |= baudRate;
				break;
			case SPI_2:
				SPI2->CTAR[0] &= ~(SPI_CTAR_BR_MASK);
				SPI2->CTAR[0] |= baudRate;
				break;
	}
}

/*!
	@brief     This function selects if MSB or LSM bits is first transmitted.
	@param[in] spi_channel_t
	@param[in] uint32_t
	@return	   static void
 */
static void SPI_msb_first(spi_channel_t channel, spi_lsb_or_msb_t msb)
{
	switch(channel)
	{
	case SPI_0:
		if(SPI_MSB == msb)
			SPI0->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
		else if(SPI_LSM == msb)
			SPI0->CTAR[0] |= (SPI_CTAR_LSBFE_MASK);
		break;
	case SPI_1:
			if(SPI_MSB == msb)
				SPI1->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			else if(SPI_LSM == msb)
				SPI1->CTAR[0] |= (SPI_CTAR_LSBFE_MASK);
			break;
	case SPI_2:
			if(SPI_MSB == msb)
				SPI2->CTAR[0] &= ~(SPI_CTAR_LSBFE_MASK);
			else if(SPI_LSM == msb)
				SPI2->CTAR[0] |= (SPI_CTAR_LSBFE_MASK);
			break;
	}
}

/*!
	@brief     This function starts the SPI transmission by modifying
		   the value of HALT bit.
	@param[in] spi_channel_t
	@return	   void
 */
void SPI_start_tranference(spi_channel_t channel)
{
	switch(channel)
	{
		case SPI_0:
			SPI0->MCR &= ~(SPI_MCR_HALT_MASK);
			break;
		case SPI_1:
			SPI1->MCR &= ~(SPI_MCR_HALT_MASK);
			break;
		case SPI_2:
			SPI2->MCR &= ~(SPI_MCR_HALT_MASK);
			break;
	}
}

/*!
	@brief     This function stops the SPI transmission by modifying
		   the value of HALT bit.
	@param[in] spi_channel_t
	@return	   void
 */
void SPI_stop_tranference(spi_channel_t channel)
{
	switch (channel) {
	case SPI_0:
		SPI0->MCR |= (SPI_MCR_HALT_MASK);
		break;
	case SPI_1:
		SPI1->MCR |= (SPI_MCR_HALT_MASK);
		break;
	case SPI_2:
		SPI2->MCR |= (SPI_MCR_HALT_MASK);
		break;
	}
}

/*!
	@brief     This function transmits the information contained in data.
	@param[in] uint8_t
	@return	   void
 */
void SPI_send_one_byte(uint8_t Data)
{
	SPI0->PUSHR = Data;
	while(0 == (SPI0->SR & SPI_SR_TCF_MASK));
	/*Con esta mascara se escribe un 1 en el SR para limpiar*/
	SPI0->SR |= SPI_SR_TCF_MASK;
}

 /*!
	@brief     This function configures the SPI for transmission.
	@param[in] pointer to constant (const spi_config_t*)
	@return	   void
  */
void SPI_init(const spi_config_t* SPI_Config)
{
  /** Activate clock gating for the SPI **/
  SPI_clk(SPI_Config->spi_channel);
  /** Activate clock gating for the GPIO **/
  GPIO_clock_gating(SPI_Config->spi_gpio_port.gpio_port_name);

  GPIO_pin_control_register(SPI_Config->spi_gpio_port.gpio_port_name, SPI_Config->spi_gpio_port.spi_clk, &(SPI_Config->pin_config));

  GPIO_pin_control_register(SPI_Config->spi_gpio_port.gpio_port_name, SPI_Config->spi_gpio_port.spi_sout, &(SPI_Config->pin_config));
  /** Configure the SPI as master **/
  SPI_set_master(SPI_Config->spi_channel,SPI_Config->spi_master);

  SPI_fifo(SPI_Config->spi_channel,SPI_Config->spi_enable_fifo);
  /** Enable the clock modules of the SPI **/
  SPI_enable(SPI_Config->spi_channel);
  /* selects the clock polarity depending on the value of cpol.*/
  SPI_clock_polarity(SPI_Config->spi_channel, SPI_Config->spi_polarity);

  SPI_frame_size(SPI_Config->spi_channel, SPI_Config->spi_frame_size);

  SPI_clock_phase(SPI_Config->spi_channel, SPI_Config->spi_phase);

  SPI_baud_rate(SPI_Config->spi_channel, SPI_Config->spi_baudrate);

  SPI_msb_first(SPI_Config->spi_channel, SPI_Config->spi_lsb_or_msb);
}
