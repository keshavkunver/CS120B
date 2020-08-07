/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #3  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0x00;	PORTB = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;
	
	//temp variable initializations
	unsigned char manipA;
	unsigned char manipB;
	unsigned numOnes;

    /* Insert your solution below */
    while (1) 
    {
	//set temp variables for bit manipulation
	manipA = PINA;
	manipB = PINB;
	numOnes = 0x00;

	//loop through 8 bits and increase number of 1s  accordingly
	for(int i = 0; i < 8; i++)
	{
		//check first PINA bit == 1  and update
		if(manipA & 0x01)
			numOnes++;

		//check first PINB bit == 1 and update
		if(manipB & 0x01)
			numOnes++;
		
		//shift over bits
		manipA = manipA >> 1;
		manipB = manipB >> 1;
	}	
	
	//set total number of ones in PORTC
	PORTC = numOnes;
    }
    return 1;
}
