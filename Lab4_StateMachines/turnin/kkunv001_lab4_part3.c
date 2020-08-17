/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum Light_States { Start, Init, Check_Num, Check_Y, Wait_Y, Unlock,  } state;

//unsigned char button1;
//unsigned char button2;

//skeleton code from zyBooks
void TickFct_Lock()
{
  switch(state)  // Transitions
  {   
	case Start:
        	state = Init;
        	break;
	
	case Init:
		if(PINA & 0x04) {
			state = Check_Num;
		}
		break;

	case Check_Num:
		if(PINA == 0x00) {
			state = Check_Y;
		}
		else if(PINA == 0x04) {
			state = Check_Num;
		}
		else {
			state = Init;
		}
		break;

	case Check_Y:
		if(PINA & 0x02) {
			state = Wait_Y;
		}
		else if(PINA == 0x00) {
			state = Check_Y;
		}
		else {
			state = Init;
		}
		break;

	case Wait_Y:
		if(PINA == 0x00) {
			state = Unlock;
		}
		else if( PINA == 0x02) {
			state = Wait_Y;
		}
		else {
			state = Init;
		}

	case Unlock:
		if(PINA & 0x80) {
			state = Init;
		}
		else {
			state = Unlock;
		}
		break;

     	default:
        	break;
  } 

  switch(state) // State actions
  {   
     	case Start:
        	break;		

	case Init:
		PORTB = 0x00;
		PORTC = 0x00;
		break;

	case Check_Num:
		PORTC = 0x01;
		break;

	case Check_Y:
		PORTC = 0x02;
		break;

	case Wait_Y:
		PORTC = 0x03;
		break;

	case Unlock:
		PORTB = 0x01;
		PORTC = 0x04;
		break;

     	default:
        	break;
   }
}
  
int main(void) 
{
    /* Insert DDR and PORT initializations */
	//DDRA = 0x00;	PORTA = 0xFF;
	//DDRC = 0xFF;	PORTC = 0x00;

    	state = Start;
	PORTC = 0x00;
	//button1 = ~PINA & 0x01;
    	//button2 = ~PINA & 0x02;

    /* Insert your solution below */
    while (1) 
    {
	TickFct_Lock();
    }
    return 1;
}
