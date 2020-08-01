/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

	unsigned char cntavail = 0x00;

    /* Insert your solution below */
    while (1) 
    {
	    //don't change PINA value
	    unsigned char temp = PINA;

	    //check PA3-PA0 one by one
	    for(int i = 0; i < 4; i++)
	    {
		//if bit != 1 space is available
		if(!(temp & 0x01))
			cntavail++;

		//shift one after checking first bit
		temp = temp >> 1;
	    }
	    PORTC = cntavail;
    }
    return 1;
}
