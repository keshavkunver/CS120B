/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
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

	//buttons represent fuel level
	unsigned char buttons;

	unsigned char output;

    /* Insert your solution below */
    while (1) 
    {
	//temp variables for bit manipulation
	    buttons = ~PINA & 0x0F;
	    output = 0x00;

	    //check at 0 and make way up towards 15

	    //no gas, only set PC6
	    if(buttons == 0)
		    output = SetBit(output, 6, 1);

	    // fuelLevel 1 or greater, P5 and still P6
	    if(buttons >= 1)
	    {
		    output = SetBit(output, 5, 1);
		    //gas is still low
	   	    output = SetBit(output, 6, 1);
	    }

	    // fuelLevel 3 or greater, P4 & P5 & still P6
	    if(buttons >= 3)
	    {
		    output = SetBit(output, 4, 1);
		    output = SetBit(output, 6, 1);
	    }

	    // fuelLevel 5 or greater, P3 & P4 & P5 & no more P6
	    if(buttons >= 5)
	    {
		    output = SetBit(output, 3, 1);
		    output = SetBit(output, 6, 0);
	    }

	    // fuelLevel 7 or greater, P2 & P3 & P4 & P5
	    if(buttons >= 7)
		    output = SetBit(output, 2, 1);

	    // fuelLevel 10 or greater, P1 & P2 & P3 & P4 & P5
	    if(buttons >= 10)
		   output = SetBit(output, 1, 1);

	    if(buttons >= 13)
		    output = SetBit(output, 0, 1);

	    //set PORTC to calculated output
	    PORTC = output;
    }
    return 1;
}
