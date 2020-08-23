
/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #7  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

void ADC_init()
{
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;	
	DDRB = 0xFF;	PORTB = 0x00;
	
	const unsigned short MAX = 975;	// =  7,8 LEDS = 2^6 + 2^7
					// = 64 + 128 = 192
	unsigned short my_short;

	ADC_init();

    /* Insert your solution below */
    	while (1) 
	{
		my_short = ADC;

		if(my_short >= MAX/2) {
			PORTB = 0x01;
		}
		else {
			PORTB = 0x00;
		}	
    	}
    return 1;
}
