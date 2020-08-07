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
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;
	DDRC = 0xFF;	PORTC = 0x00;
	
	//temp variable initializations
	unsigned char bottomB;
	unsigned char topC;

    /* Insert your solution below */
    while (1) 
    {
	    //take top 4 bits from PINA
	    bottomB = PINA & 0xF0;
	    //shift them right to the bottom of PORTB
	    bottomB = bottomB >> 4;

	    //take bottom 4 bits from PINA
	    topC = PINA & 0x0F;
	    //shift them left to the top of PORTC
	    topC = topC << 4;

	    //update PORTB and PORTC
	    PORTB = bottomB;
	    PORTC = topC;
    }
    return 1;
}
