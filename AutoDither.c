/*
 * AutoDither.c
 * Provides dithering solution to EQ3-2 mount, unguided
 * Takes input from Synscan handcontroller, camera control pin
 * Controls Autoguider port on mount and passes on camera control
 *
 * Input from handcontroller is A7
 * Output to camera is A5
 * Led indicating dithering on A4
 * A0 .. A3 is autoguide control
 * A0: RA+
 * A1: Dec+
 * A2: Dec-
 * A3: RA-
 *
 * Created: 2016-03-05 23:16:18
 *  Author: Wim
 */ 


#ifndef F_CPU
#define F_CPU 1000000ul
#endif
#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define RAp PA0
#define Decp PA1
#define Decm PA2
#define RAm PA3
#define StatOut PA4
#define CamOut PA5

char ditherpath[]="21448822211144448888222221111144444488888822222221111111444444448888888822222222211111111144444444448888888888";
uint8_t IsDithering;
uint8_t DitherCounter;
uint8_t CamIn;
int main(void)
{
	DDRA = 0x3f;  //sets PA0 ... PA5 as output, PA6 and PIN7 as input
	PORTA &= 0xc0;
	//_delay_ms(150);
	IsDithering = 0;
	DitherCounter = 0;
    while(1)
    {
		while (IsDithering==0)  // waiting for first exposure
		{
			CamIn = (PINA&0x80); // get PINA7
			if (CamIn==0)
			{  // when PINA7 goes low, exposure is started
				PORTA |= (1<<CamOut);
				IsDithering = 1;
			}
			else
			{
				PORTA &= ~(1<<CamOut);
			}
			//_delay_ms(150);
		} // end waiting for first exposure
	    CamIn = (PINA&0x80);
		while (CamIn == 0)
		{   // exposure
			PORTA |= (1<<CamOut);
			PORTA &= ~((1<<RAp) | (1<<RAm) | (1<<Decp) | (1<<Decm) | (1<<StatOut));
	        CamIn = (PINA&0x80);
		}
	    CamIn = (PINA&0x80);
		while (CamIn!=0)
		{   // between exposures
			PORTA &= ~(1<<CamOut);
			
			PORTA |= ((ditherpath[DitherCounter] & 0x0f) | (1<<StatOut));
	        CamIn = (PINA&0x80);
			
		}
		DitherCounter +=1;
		if (DitherCounter>=110)
		{
			DitherCounter = 0;
		}
		//_delay_ms(150);
    }
}