/*	Author: lab
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#endif

enum Light_States { Light } state;

unsigned char light = 0x00;
unsigned char i = 0x00;

void Light_Blink()
{
	switch(state) {	//Transitions
		case Light:
			state = Light;
			break;
		default:
			break;
	}

	switch(state) {	//Actions
		case Light:
			if(i == 0) {
				PORTB = 0x01;
				i++;
			}
			else if(i == 1) {
				PORTB = 0x02;
				i++;
			}
			else if(i == 2) {
				PORTB = 0x04;
				i = 0;
			}
			break;
		default:
			break;
	}
}

int main(void) 
{
    /* Insert DDR and PORT initializations */
	//DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;

	TimerSet(1000);
	TimerOn();
	
	state = Light;
    /* Insert your solution below */
    while (1) 
    {
	//one tick
	Light_Blink();

	//wait for period
	while(!TimerFlag) {}
	TimerFlag = 0;
		
    }
    return 1;
}
