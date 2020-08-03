/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #4
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
	DDRB = 0x00;	PORTB = 0xFF;
	DDRC = 0x00;	PORTC = 0xFF;
	DDRD = 0xFF;	PORTD = 0x00;

    /* Insert your solution below */
    while (1) 
    {
	    //get weight input
	    unsigned short totalWeight = PINA + PINB + PINC;
	    unsigned char differenceAC = PINA - PINC;

	    //if weight > 140, set PD0 to 1
	    if(totalWeight > 0x8C)
		    PORTD = PORTD | 0x01;

	    //if A-C > 80, set PD1 to 1
	    if(differenceAC > 0x50)
		    PORTD = PORTD | 0x02;

	    //set PD7-PD2 to be total weight
	    
    }
    return 1;
}
