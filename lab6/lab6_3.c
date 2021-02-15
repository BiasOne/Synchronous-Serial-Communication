/*
 * lab6_3.c
 *
 * Created: 7/19/2020 12:01:51 AM
 *  Author: josep
 */ 
#include <stdio.h>
#include <avr/io.h>
#include "lsm6ds3.h"
#include "lsm6ds3_registers.h"
#include "spi.h"

uint8_t *ptr=0x2000;

int main(void)
{
	spi_init();

	while (1)
	{
	*ptr=lsm6ds3_read(WHO_AM_I);			
	}
}