/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
#include "keypad.h"
#include "scheduler.h"
#endif

unsigned char out = 0x00;

enum KeypadStates {Start, Output} state;

int Keypad_Tick(int state)
{
	
	unsigned char x;
	x = GetKeypadKey();

	switch(state)	//Transitions
	{		
		case Start:
			state = Output;
			break;
		case Output:
			state = Output;
			break;
		default:
			state = Start;
			break;
	}

	switch(state)	//Actions
	{
		case Start:
			break;
		case Output:
			switch(x)
			{
				case '\0':
					out = 0x1F;
					break;
				case '1':
					out = 0x80;
					break;
				case '2':
					out = 0x80;
					break;
				case '3':
					out = 0x80;
					break;
				case '4':
					out = 0x80;
					break;
				case '5':
					out = 0x80;
					break;
				case '6':
					out = 0x80;
					break;
				case '7':
      					out = 0x80;
      					break;
      				case '8':
      					out = 0x80;
      					break;
      				case '9':
      					out = 0x80;
      					break;
      				case 'A':
      					out = 0x80;
      					break;
      				case 'B':
      					out = 0x80;
      					break;
      				case 'C':
      					out = 0x80;
      					break;
      				case 'D':
      					out = 0x80;
      					break;
      				case '*':
      					out = 0x80;
      					break;
      				case '0':
      					out = 0x80;
      					break;
      				case '#':
      					out = 0x80;
      					break;
      				default:
      					out = 0x1B;
      					break;
			}
		default:
			break;
	}

	PORTB = out;
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF;	PORTB = 0x00;
	DDRC = 0xF0;	PORTC = 0x0F;	//Keypad Input/Output
    
	unsigned char i;

	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	//Task1
	task1.state = 0;	//Task initial state
	task1.period = 1;	//Task Period
	task1.elapsedTime = task1.period; //Task current elapsed time
	task1.TickFct = &Keypad_Tick;

	TimerSet(2);
	TimerOn();

    /* Insert your solution below */
    while (1) {
	

	for ( i = 0; i < numTasks; i++ ) 
	{
   		if ( tasks[i]->elapsedTime == tasks[i]->period ) 
		{
   			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
   			tasks[i]->elapsedTime = 0;
   		}

   		tasks[i]->elapsedTime += 1;
   	}
   		while(!TimerFlag);
   		TimerFlag = 0;
    }
    return 1;
}
