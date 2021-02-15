
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "lsm6ds3.h"
#include "lsm6ds3_registers.h"
#include "spi.h"
#include "usart.h"

volatile uint8_t accel_flag;



int main(void)
{
	
	PORTC_DIRCLR = 0b01000000;
	PORTC_INTCTRL = 0x01;
	PORTC_INT0MASK = 0b01000000;
	PORTC_PIN6CTRL= 0b00000001;
	
	PMIC_CTRL = PMIC_LOLVLEN_bm;
	sei();
	
	accel_flag=0;
	lsm6ds3_init();
	usartd0_init();
	
		int dispTOP =0;
		int dispBOT =0;
		int dispRIGHT =0;
		int dispLEFT =0;
		
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
			
			int16_t xData = accel_XL | (accel_XH << 8);
			int16_t yData = accel_YL | (accel_YH << 8);
			int16_t zData = accel_ZL | (accel_ZH << 8);
			
		
			
			if (zData >= 15000 && dispTOP == 0) // right side up
			{
				char TopSideUp[12]= {'T','O','P',' ','S','I','D','E',' ','U','P',' '};
				for (int i=0; i < sizeof(TopSideUp); i++)
					{
						usartd0_out_char(TopSideUp[i]);
					}
				dispTOP =1;
				dispBOT =0;
				dispRIGHT =0;
				dispLEFT =0;
				
			}
			else if(zData <= -15000 && dispBOT == 0)
			{
				char BottomSideUp[15]= {'B','O','T','T','O','M',' ','S','I','D','E',' ','U','P',' '};
					for (int i=0; i < sizeof(BottomSideUp); i++)
					{
						usartd0_out_char(BottomSideUp[i]);
					}
					
					dispTOP =0;
					dispBOT=1;
					dispRIGHT =0;
					dispLEFT =0;
					
			}
			else if(xData >= 15000 && dispRIGHT == 0)
			{
			
				char RightSideUp[14]= {'R','I','G','H','T',' ','S','I','D','E',' ','U','P',' '};
					for (int i=0; i < sizeof(RightSideUp); i++)
					{
						usartd0_out_char(RightSideUp[i]);
					}
					dispBOT=0;
					dispTOP =0;
					dispRIGHT =1;
					dispLEFT =0;
			}
			else if(xData <= -15000 && dispLEFT ==0)
			{
				
				char LeftSideUp[13]= {'L','E','F','T',' ','S','I','D','E',' ','U','P',' '};
					for (int i=0; i < sizeof(LeftSideUp); i++)
					{
						usartd0_out_char(LeftSideUp[i]);
					}
					dispBOT=0;
					dispTOP =0;
					dispRIGHT =0;
					dispLEFT =1;
			}
		}     		      
	}
}

ISR(PORTC_INT0_vect)
{
	PORTC_INTFLAGS =0b00000001;
	accel_flag=1;
}