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


unsigned char currLetter;	//letter to be outputted
unsigned char myIndex = 0;	//index for netID array
const unsigned char netID[8] = {'k','k','u','n','v', '0', '0', '1', "\0"};	//netID

enum CharStates {Char_Init, Get};

enum OutputStates {Out_Init, Display, Off};


//Gets input
int Char_Tick(int state)
{
	switch(state)	//Transitions
	{
		case Char_Init:
			state = Get;
			break;
		case Get:
			//set currLetter unless current index is null terminal character
			if(currLetter != '\0')
			{
				state = Get;
			}
			else
			{
				state = Char_Init;
			}
			break;
		default:
			state = Char_Init;
			break;
	}

	switch(state)	//Actions
	{
		case Char_Init:
			myIndex = 0;
			break;
		case Get:
			currLetter = netID[myIndex];
			myIndex++;
			break;
		default:
			state = Char_Init;
			break;
	}
	
	return state;
}

//Outputs the answer onto the board
int LCD_Tick(int state)
{ 
	switch(state)	//Transitions
	{
		case Out_Init:
			state = Display;
			break;
		case Display:
			//output as long as index is not null terminal character
			if(currLetter != '\0')
			{
				state = Display;
			}
			else
			{
				state = Off;
			}
			break;
		case Off:
			state = Out_Init;
			break;
		default:
			state = Out_Init;
			break;
	}

	switch(state)	//Actions
	{
		case Out_Init:
			LCD_Cursor(1);
			break;
		case Display:	//Display the current letter
			LCD_WriteData(currLetter);
			break;
		case Off:	//Remove display
			LCD_ClearScreen();
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
	static task task1, task2;
	task *tasks[] = { &task1, &task2 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	//Task1
	task1.state = 0;	//Task initial state
	task1.period = 250;	//Task Period
	task1.elapsedTime = task1.period; //Task current elapsed time
	task1.TickFct = &LCD_Tick;

	//Task2
	task2.state = 0;	//Task initial state
	task2.period = 250;	//Task Period
	task2.elapsedTime = task2.period; //Task current elapsed time
	task2.TickFct = &Char_Tick;

	//Set on/off flashing to 1 second
	TimerSet(250);
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

   		tasks[i]->elapsedTime += 250; //GCD
   	}
   		while(!TimerFlag);
   		TimerFlag = 0;
    }
    return 1;
}
