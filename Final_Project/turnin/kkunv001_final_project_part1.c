/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Final Project Exercise #1
 *	Exercise Description: Getting output onto the LCD Display
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#include "timer.h"
#include "scheduler.h"
#endif


//Display function uses a const string, but not needed
const unsigned char* string = "Pizza";

enum States {Init, Display, Off};

int LCD_Tick(int state)
{

	switch(state)	//Transitions
	{
		case Init:
			state = Display;
			break;
		case Display:
			state = Off;
			break;
		case Off:
			state = Display;
			break;
		default:
			state = Init;
			break;
	}

	switch(state)	//Actions
	{
		case Init:
			break;
		case Display:	//Display favorite food
			LCD_DisplayString(1, string );
			break;
		case Off:	//Remove favorite food
			LCD_ClearScreen();
			break;
		default:
			break;
	}

	return state;
}
int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF;	PORTC = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;
	
	unsigned char i;

	//Declare an array of tasks
	static task task1;
	task *tasks[] = { &task1 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	//Task1
	task1.state = 0;	//Task initial state
	task1.period = 1000;	//Task Period
	task1.elapsedTime = task1.period; //Task current elapsed time
	task1.TickFct = &LCD_Tick;

	//Set on/off flashing to 1 second
	TimerSet(1000);
	TimerOn();

	LCD_init();
    /* Insert your solution below */
    while (1) 
    {
	for ( i = 0; i < numTasks; i++ ) 
	{
   		if ( tasks[i]->elapsedTime == tasks[i]->period ) 
		{
   			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
   			tasks[i]->elapsedTime = 0;
   		}

   		tasks[i]->elapsedTime += 1000; //GCD
   	}
   		while(!TimerFlag);
   		TimerFlag = 0;
    }
    return 1;
}
