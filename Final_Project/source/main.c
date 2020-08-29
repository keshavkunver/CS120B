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
unsigned char myIndex = 0;	//index for alphabet array
const unsigned char alphabet[26] = {'a','b','c','d','e', 'f', 'g', 'h', 'i',
					'j','k','l','m','n','o', 'p','q', 'r',
					's','t','u','v','w','x','y','z'};

unsigned char button1;
unsigned char button2;
unsigned char button3;
unsigned char cursor = 1;
unsigned char resetFlag = 0;

enum CharStates {Char_Init, Wait, Increment, Decrement, Next};

enum OutputStates {Out_Init, Display};


//Gets input
int Char_Tick(int state)
{
	switch(state)	//Transitions
	{
		case Char_Init:
			state = Wait;
			break;
		case Wait:
			if(button1 && !button2)
			{
				state = Increment;
			}
			else if(!button1 && button2)
			{
				state = Decrement;
			}
			
			else if(button1 && button2)
			{
				state = Char_Init;
			}
			else
			{
				state = Wait;
			}
			break;
		case Increment:
			if(button1 && button2)
			{
				state = Char_Init;
			}
			else if(button1 && !button2)
			{
				state = Increment;				
			}
			else if(!button1)
			{
				state = Wait;
			}
			break;
		case Decrement:
			if(button1 && button2)
			{
				state = Char_Init;
			}
			else if(!button1 && button2)
			{
				state = Decrement;				
			}
			else if(!button2)
			{
				state = Wait;
			}
			break;
		case Next:
			if(button1 && button2)
			{
				state = Char_Init;
			}
			else if(button3)
			{
				state = Next;
			}
			else if(!button3)
			{
				state = Wait;
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
			cursor = 1;
			resetFlag = 1;
			break;
		case Wait:
			resetFlag = 0;
			currLetter = alphabet[myIndex];
			break;
		case Increment:
			if(currLetter != 'a')
			{
				myIndex--;
			}
			currLetter = alphabet[myIndex];
			break;
		case Decrement:
			if(currLetter != 'z')
			{
				myIndex++;
			}
			currLetter = alphabet[myIndex];
			break;
		case Next:
			cursor++;
			break;
		default:
			state = Char_Init;
			break;
	}
	
	return state;
}

//Outputs the character onto the board
int LCD_Tick(int state)
{ 
	switch(state)	//Transitions
	{
		case Out_Init:
			state = Display;
			break;
		case Display:
			if(resetFlag == 0)
			{
				state = Display;
			}
			else if(resetFlag == 1)
			{
				state = Out_Init;
			}
			break;
		default:
			state = Out_Init;
			break;
	}

	switch(state)	//Actions
	{
		case Out_Init:
			LCD_ClearScreen();
			LCD_Cursor(1);
			LCD_WriteData('a');
			break;
		case Display:	//Display the current letter at desired cursor
			LCD_Cursor(cursor);
			LCD_WriteData(currLetter);
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
	DDRA = 0x00;	PORTA = 0xFF;
	
	unsigned char i;

	//Declare an array of tasks
	static task task1, task2;
	task *tasks[] = { &task1, &task2 };
	const unsigned short numTasks = sizeof(tasks)/sizeof(task*);

	//Task1
	task1.state = 0;	//Task initial state
	task1.period = 500;	//Task Period
	task1.elapsedTime = task1.period; //Task current elapsed time
	task1.TickFct = &LCD_Tick;

	//Task2
	task2.state = 0;	//Task initial state
	task2.period = 500;	//Task Period
	task2.elapsedTime = task2.period; //Task current elapsed time
	task2.TickFct = &Char_Tick;

	//GCD
	TimerSet(500);
	TimerOn();

	LCD_init();
    /* Insert your solution below */
    while (1) 
    {
	//button initializations
	button1 = ~PINA & 0x01;
	button2 = ~PINA & 0x02;
	button3 = ~PINA & 0x04;

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
