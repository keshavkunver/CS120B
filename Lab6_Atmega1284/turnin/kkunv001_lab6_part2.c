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

//increment and decrement buttons
#define button1 (~PINA & 0x01)
#define button2 (~PINA & 0x02)

enum States { Start, Init, Action, Inc, Dec, Wait_Inc, Wait_Dec } state;

void Tick()
{
	switch(state)	//Transitions
	{
		case Start:
			state = Init;
			break;
		case Init:
			if(!button1 && !button2)
				state = Init;
			else
				state = Action;
			break;
		case Action:
			if(button1 && !button2)
				state = Inc;
			else if(!button1 && button2)
				state = Dec;
			else if(button1 && button2)
				state = Init;
			break;
		case Inc:
			if(!button1)
				state = Wait_Inc;
			else if(button1 && button2)
				state = Init;
			else if(button1)
				state = Inc;
			break;
		case Dec:
			if(!button2)
				state = Wait_Dec;
			else if(button1 && button2)
				state = Init;
			else if(button2)
				state = Dec;
			break;
		case Wait_Inc:
			state = Action;
			break;
		case Wait_Dec:
			state = Action;
			break;
		default:
			state = Init;
			break;
	}

	switch(state)
	{
		case Init:
			PORTC = 0x00;
			break;
		case Inc:
			break;
		case Dec:
			break;
		case Wait_Inc:
			if(PORTC < 9)
				PORTC++;
			break;
		case Wait_Dec:
			if(PORTC > 0)
				PORTC--;
			break;
		case Action:
			break;
		default:
			break;
	}
}


int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRC = 0xFF;	PORTC = 0x00;

	state = Start;
	

    /* Insert your solution below */
    while (1) 
    {
	Tick();
    }
    return 1;
}
