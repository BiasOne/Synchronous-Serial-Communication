/*------------------------------------------------------------------------------
  spi.c --
  
  Description:
    Provides useful definitions for manipulating the relevant SPI
    module of the ATxmega128A1U. 
  
  Author(s): Dr. Eric M. Schwartz and Wesley Piard
  Last modified by: Christopher Crary
  Last modified on: 15 July 2020
------------------------------------------------------------------------------*/

/********************************DEPENDENCIES**********************************/

#include <avr/io.h>
#include "spi.h"

/*****************************END OF DEPENDENCIES******************************/


/*****************************FUNCTION DEFINITIONS*****************************/


void spi_init(void)
{
  /* Configure pin direction of relevant SPI signals. */
  PORTF.OUTSET = CS_bm | MOSI_bm | SCK_bm | MISO_bm;
  PORTF.DIRSET = CS_bm | MOSI_bm | SCK_bm;
  PORTF.DIRCLR = MISO_bm;
   
	
	/* Set the other relevant SPI configurations. */
	SPIF.CTRL	=	SPI_PRESCALER1_bm | SPI_MASTER_bm | SPI_MODE_3_gc | SPI_ENABLE_bm;
}

void spi_write(uint8_t data)
{
	/* Write to the relevant DATA register. */
	SPIF.DATA = data;

	/* Wait for relevant transfer to complete. */
	while((SPIF.STATUS & SPI_IF_bm) != SPI_IF_bm);
}

uint8_t spi_read(void)
{
  /* Write some arbitrary data to initiate a transfer. */
  SPIF.DATA = 0x37;

  /* Wait for relevant transfer to be complete. */
  while((SPIF.STATUS & SPI_IF_bm) != SPI_IF_bm);

	/* After the transmission, return the data that was received. */
	return SPIF.DATA;
}

/***************************END OF FUNCTION DEFINITIONS************************/
