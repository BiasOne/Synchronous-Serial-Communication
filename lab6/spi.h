#ifndef SPI_H_		// Header guard.
#define SPI_H_

/*------------------------------------------------------------------------------
  spi.h --
  
  Description:
    Provides function prototypes and macro definitions for utilizing the SPI
    system of the ATxmega128A1U. 
  
  Author(s): Dr. Eric M. Schwartz and Wesley Piard
  Last modified by: Christopher Crary
  Last modified on: 15 July 2020
------------------------------------------------------------------------------*/

/********************************DEPENDENCIES**********************************/

#include <avr/io.h>

/*****************************END OF DEPENDENCIES******************************/

/***********************************MACROS*************************************/

#define SCK_bm			(1<<7)
#define MISO_bm			(1<<6)
#define MOSI_bm			(1<<5)
#define CS_bm			(1<<4)
//bit 3 is empty
//bit 2 is empty
#define SCL_bm			(1<<1)
#define SDA_bm			(1<<0)

#define INT2_bm			(1<<7)
#define INT1_bm			(1<<6)
//bit 5 is empty
#define EN_STBY		    (1<<4)
#define BIN1_bm			(1<<3)
#define AIN2_bm			(1<<2)
#define PWMB_bm			(1<<1)
#define PWMA_bm			(1<<0)


/********************************END OF MACROS*********************************/

/*****************************FUNCTION PROTOTYPES******************************/

/*------------------------------------------------------------------------------
  spi_init -- 
  
  Description:
    Initializes the relevant SPI module to communicate with the LSM6DS3.

  Input(s): N/A
  Output(s): N/A
------------------------------------------------------------------------------*/
void spi_init(void);

/*------------------------------------------------------------------------------
  spi_write -- 
  
  Description:
    Transmits a single byte of data via the relevant SPI module.

  Input(s): `data` - 8-bit value to be written via the relevant SPI module. 
  Output(s): N/A
------------------------------------------------------------------------------*/
void spi_write(uint8_t data);

/*------------------------------------------------------------------------------
  spi_read -- 
  
  Description:
    Reads a byte of data via the relevant SPI module.

  Input(s): N/A
  Output(s): 8-bit value read from the relevant SPI module.
------------------------------------------------------------------------------*/
uint8_t spi_read(void);

/**************************END OF FUNCTION PROTOTYPES**************************/

#endif // End of header guard.