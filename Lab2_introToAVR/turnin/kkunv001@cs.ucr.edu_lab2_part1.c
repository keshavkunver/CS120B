/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #2  Exercise #1
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
	DDRB = 0xFF;	PORTB = 0x00;

    /* Insert your solution below */
    while (1) 
    {
	   //PA0 and PA1
	   unsigned char garageDoor = PINA & 0x01;
	   unsigned char lightSensor = PINA & 0x02;
	  
	   //PORTB = !PA1 & PA0
	   PORTB = !lightSensor & garageDoor;
    }
    return 1;
}
