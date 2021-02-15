#include <avr/io.h>
#include <avr/interrupt.h>
#include "lsm6ds3.h"
#include "lsm6ds3_registers.h"
#include "spi.h"
#include "usart.h"

volatile uint8_t accel_flag;



int main(void)
{	
	
	PORTC.DIRCLR = 0b01000000;
	PORTC.INTCTRL = 0x01;
	PORTC.INT0MASK = 0b01000000;
	PORTC.PIN6CTRL= 0b00000001;
	
	PMIC_CTRL = PMIC_LOLVLEN_bm;
	sei();
	
	accel_flag=0;
	lsm6ds3_init();
	usartd0_init();
	
	while(1)
	{
		if(accel_flag == 1)//interupt broken
		{	
		accel_flag=0;
		volatile uint8_t accel_XL=lsm6ds3_read(OUTX_L_XL);
		volatile uint8_t accel_XH=lsm6ds3_read(OUTX_H_XL);
		
		volatile uint8_t accel_YL=lsm6ds3_read(OUTY_L_XL);
		volatile uint8_t accel_YH=lsm6ds3_read(OUTY_H_XL);
		
		volatile uint8_t accel_ZL=lsm6ds3_read(OUTZ_L_XL);
		volatile uint8_t accel_ZH=lsm6ds3_read(OUTZ_H_XL);
		
		usartd0_out_char(accel_XL);
		usartd0_out_char(accel_XH);
		
		usartd0_out_char(accel_YL);
		usartd0_out_char(accel_YH);
		
		usartd0_out_char(accel_ZL);
		usartd0_out_char(accel_ZH);
		
		}		
	}	
}

ISR(PORTC_INT0_vect)
{
	PORTC_INTFLAGS =0b00000001;
	accel_flag=1;
}