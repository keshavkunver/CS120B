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

	unsigned char cntavail;

    /* Insert your solution below */
    while (1) 
    {
	    cntavail = 0x00;

	    //!PA0
	    if( !(PINA & 0x01) )
		    cntavail++;
	    //!PA1
	    if( !(PINA & 0x02) )
		    cntavail++;
	    //!PA2
	    if( !(PINA & 0x04) )
		   cntavail++;
	    //!PA3
	    if( !(PINA & 0x08) )
		   cntavail++;

	    PORTC = cntavail;   
    }
    return 1;
}
