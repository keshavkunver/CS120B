/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum Light_States { Start, Light1, Button_Press, Button_Release, Light_Back  } state;

//skeleton code from zyBooks
void TickFct_Lights()
{
  switch(state)  // Transitions
  {   
     case Start:
        state = Light1;
        break;

     case Light1:
        if (PINA & 0x01) {
           state = Button_Press;
        }
        else if(!(PINA & 0x01) ){
           state = Light1;
        } 
        break;

     case Button_Press:
        if (PINA & 0x01) {
           state = Button_Press;
        }
        else if(!(PINA & 0x01) ){
           state = Button_Release;
        }
        break;

     case Button_Release:
	if(PINA & 0x01) {
	   state = Light_Back;
	}
	else if(!(PINA & 0x01) ) {
	   state = Button_Release;
	}
	break;

     case Light_Back:
	if(PINA & 0x01) {
	   state = Light_Back;
	}
	else if(!(PINA & 0x01) ) {
	   state = Light1;
	}
	break;

     default:
        state = Light1;
        break;
  } 

  switch(state) // State actions
  {   
     case Light1:
	PORTB = 0x01;
        break;

     case Button_Press:
        PORTB = 0x02;
        break;

    case Button_Release:
        PORTB = 0x02;
        break;

   case Light_Back:
        PORTB = 0x01;
        break;

     default:
        break;
   } // State actions
}
  
int main(void) 
{
    /* Insert DDR and PORT initializations */
	//DDRA = 0x00;	PORTA = 0xFF;
	//DDRB = 0xFF;	PORTB = 0x00;

    PORTB = 0x00;
    state = Start;
    /* Insert your solution below */
    while (1) 
    {
	TickFct_Lights();

    }
    return 1;
}
