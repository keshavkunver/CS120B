/*	Author: lab
 *  Partner(s) Name:
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #2
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


unsigned char button;
enum Light_States { Start, B_zero, B_one, B_two, Button_Press } state;

void Light_Game()
{
	switch(state)	//Transitions
	{
		case Start:
			state = B_zero;
			break;
		case B_zero:
			state = B_one;
			break;
		case B_one:
			state = button ? Button_Press : B_two;
			break;
		case B_two:
			state = B_one;
			break;
		case Button_Press:
			state = button ? Button_Press : B_zero;
			break;
		default:
			state = Start;
			break;
	}

	switch(state)	//State actions
	{
		case Start:
			PORTB = 0x00;
			break;
		case B_zero:
			PORTB = 0x01;
			break;
		case B_one:
			PORTB = 0x02;
			break;
		case B_two:
			PORTB = 0x04;
			break;
		case Button_Press:
			PORTB = 0x02;
			break;
		default:
			break;
	}
}

int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	DDRA = 0xFF;
	DDRB = 0xFF;	DDRB = 0x00;

	TimerSet(300);
	TimerOn();
	
    /* Insert your solution below */
    while (1) 
    {
	button = ~PINA & 0x01;

	//one tick
	Light_Game();

	//wait for period
	while(!TimerFlag);
	TimerFlag = 0;
		
    }
    return 1;
}
