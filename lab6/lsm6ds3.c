/*------------------------------------------------------------------------------
  lsm6ds3.c --
  
  Description:
    Brief description of file.
	  
	  Extended description, if appropriate.
  
  Author(s):
  Last modified by: 
  Last modified on: DD Month YYYY
------------------------------------------------------------------------------*/

/********************************DEPENDENCIES**********************************/

#include <avr/io.h>
#include <avr/interrupt.h> 
#include "lsm6ds3.h"
#include "lsm6ds3_registers.h"
#include "spi.h"

/*****************************END OF DEPENDENCIES******************************/


/*****************************FUNCTION DEFINITIONS*****************************/
void lsm6ds3_write(uint8_t reg_addr, uint8_t data)
{
	PORTF.OUTCLR = CS_bm;
	spi_write(reg_addr | LSM6DS3_SPI_WRITE_STROBE_bm);
	spi_write(data);
	PORTF.OUTSET = CS_bm;		
}
	
uint8_t lsm6ds3_read(uint8_t reg_addr)
{
	PORTF.OUTCLR=CS_bm;
	spi_write(reg_addr | LSM6DS3_SPI_READ_STROBE_bm);
	uint8_t data = spi_read();
	PORTF.OUTSET = CS_bm;
	return data;//dont think i need this since spi_read returns shit
}

void lsm6ds3_init(void)
{
	spi_init();	
	lsm6ds3_write(CTRL3_C, 0b00000001);
	lsm6ds3_write(CTRL1_XL, 0b01010000);
	lsm6ds3_write(CTRL9_XL, 0b00111000);
	lsm6ds3_write(INT1_CTRL, 0b00000001);
	
}


/***************************END OF FUNCTION DEFINITIONS************************/