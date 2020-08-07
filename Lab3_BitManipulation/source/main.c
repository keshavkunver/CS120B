/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #4
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

//SetBit and GetBit functions for bit manipulation
unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b)
{
	return (b ? x | (0x01 << k) : x & ~(0x01 << k));
}
unsigned char GetBit(unsigned char x, unsigned char k)
{
	return ((x & (0x01 << k)) != 0);
}

int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRD = 0x00;	PORTD = 0xFF;
	//PB0 considered an input bit
	DDRB = 0xFE;	PORTB = 0x01;
	
	//temp variable initializations
	unsigned short seatWeight;

    /* Insert your solution below */
    while (1) 
    {
	    //temp variable
	    seatWeight = PIND;

	    //shift over to account for PB0 input
	    seatWeight = seatWeight << 1;

	    //set seatWeight first bit to 1 if PB0 == 1
	    if( GetBit(PINB, 0) == 1 )
		    seatWeight = SetBit(seatWeight,0,1);

	    //if 5 < seatWeight < 70, only PB2 = 1
	    if( (seatWeight > 5) & (seatWeight < 70) )
	    {
		    PORTB = SetBit(PORTB, 2, 1);
		    PORTB = SetBit(PORTB, 1, 0);
	    }
	    // seatWeight >= 70, only PB1 = 1
	    else if(seatWeight >= 70)
	    {
		    PORTB = SetBit(PORTB, 2, 0);
		    PORTB = SetBit(PORTB, 1, 1);
	    }
	    else
	    {
		    PORTB = SetBit(PORTB, 2, 0);
		    PORTB = SetBit(PORTB, 1, 0);
	    }
    }
    return 1;
}
