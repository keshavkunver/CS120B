/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #10  Exercise #2
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

unsigned char button;
unsigned char unlocked = 0;
unsigned char myIndex;

enum KeypadStates { Start, Init, Release, Wait, Check, Correct };

enum LockStates { Lock, Unlock };

int Keypad_Tick(int state)
{
	const unsigned char code[5] = { '1', '2', '3', '4', '5' };

	unsigned char key;
	key = GetKeypadKey();

	switch(state)	//Transitions
	{		
		case Start:
			state = Init;
			break;
		case Init:
			if(key == '#') {
				state = Release;
			}
			else {
				state = Init;
			}
			break;

		//check
		case Check:
			if(key == code[myIndex]) {
				if(myIndex == 4) {
					state = Correct;
				}
				else {
					myIndex++;
					state = Release;
				}
			}
			else if(key != code[myIndex]) {
				state = Init;
			}
			break;

		case Wait:
			if(key != '\0') {
				state = Check;
			}
			else {
				state = Wait;
			}
			break;
		case Release:
			if(key == '\0') {
				state = Wait;
			}
			else {
				state = Release;
			}
			break;
		case Correct:
			state = Init;
			break;
		default:
			state = Start;
			break;
	}

	switch(state)	//Actions
	{
		case Start:
			break;
		case Init:
			myIndex = 0;
			break;
		case Check:
			break;
		case Wait:
			break;
		case Release:
			break;
		case Correct:
			unlocked = 1;
			break;
		default:
			break;
	}

	return state;
}

int Lock_Tick(int state)
{
	unsigned char out = 0x00;

	switch(state)	//Transitions
	{
		case Lock:
			if(unlocked) {
				state = Unlock;
			}
			else {
				state = Lock;
			}
			break;
		case Unlock:
			if(button) {
				state = Lock;
			}
			else {
				state = Unlock;
			}
			break;
		default:
			state = Lock;
			break;
	}

	switch(state)	//Actions
	{
		case Lock:
			out = 0x00;
			unlocked = 0;
			break;
		case Unlock:
			out = 0x01;
			break;
		default:
			break;
	}

	PORTB = out;
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */	
	DDRB = 0x7F;	PORTB = 0x80;	//PB7 is input
	DDRC = 0xF0;	PORTC = 0x0F;	//Keypad Input/Output
    
	unsigned char i;

	//Declare an array of tasks
	static task task1, task2;
	task *tasks[] = { &task1, &task2 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	//Task1
	task1.state = 0;	//Task initial state
	task1.period = 1;	//Task Period
	task1.elapsedTime = task1.period; //Task current elapsed time
	task1.TickFct = &Keypad_Tick;

	//Task2
	task2.state = 0;
	task2.period = 1;
	task2.elapsedTime = task2.period;
	task2.TickFct = &Lock_Tick;

	TimerSet(5);
	TimerOn();

    /* Insert your solution below */
    while (1) {
	
	button = ~PINB & 0x80;

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
