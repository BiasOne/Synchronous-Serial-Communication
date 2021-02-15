/*
 * lab6.c
 *
 * Created: 7/18/2020 2:33:31 PM
 * Author : joseph
 */ 

#include <avr/io.h>
#include "spi.h"


int main(void)
{
	spi_init();

    while (1) 
    {
		PORTF_OUTCLR = CS_bm;
		spi_write(0x53);
		PORTF_OUTSET = CS_bm;
		
		
    }
}

