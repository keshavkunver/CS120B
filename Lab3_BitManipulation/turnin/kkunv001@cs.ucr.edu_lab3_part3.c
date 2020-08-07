/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #3
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
	DDRC = 0xFF;	PORTC = 0x00;
	
	//temp variable initializations
	unsigned char fuelLevel;
	unsigned char output;

    /* Insert your solution below */
    while (1) 
    {
	    //temp variables for bit manipulation
	    fuelLevel = PINA & 0x0F;
	    output = 0x00;

	    //check at 0 and make way up towards 15

	    //no gas, only set PC6
	    if(fuelLevel == 0)
		    output = SetBit(output, 6, 1);

	    // fuelLevel 1 or greater, P5 and still P6
	    if(fuelLevel >= 1)
	    {
		    output = SetBit(output, 5, 1);
		    //gas is still low
	   	    output = SetBit(output, 6, 1);
	    }

	    // fuelLevel 3 or greater, P4 & P5 & still P6
	    if(fuelLevel >= 3)
	    {
		    output = SetBit(output, 4, 1);
		    output = SetBit(output, 6, 1);
	    }

	    // fuelLevel 5 or greater, P3 & P4 & P5 & no more P6
	    if(fuelLevel >= 5)
	    {
		    output = SetBit(output, 3, 1);
		    output = SetBit(output, 6, 0);
	    }

	    // fuelLevel 7 or greater, P2 & P3 & P4 & P5
	    if(fuelLevel >= 7)
		    output = SetBit(output, 2, 1);

	    // fuelLevel 10 or greater, P1 & P2 & P3 & P4 & P5
	    if(fuelLevel >= 10)
		   output = SetBit(output, 1, 1);

	    if(fuelLevel >= 13)
		    output = SetBit(output, 0, 1);


	    //now considering all bits 
	    fuelLevel = PINA;

	    //fasten seatbelt light needed, PC7 = (PA4 & PA5 & !PA6) 
	    if( (GetBit(fuelLevel, 4)) & (GetBit(fuelLevel, 5)) & ~(GetBit(fuelLevel, 6)) )
		    output = SetBit(output, 7, 1);

	    //set PORTC to calculated output
	    PORTC = output;
    }
    return 1;
}
