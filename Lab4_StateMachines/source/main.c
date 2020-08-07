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

enum Light_States { Start, ,  } state;

//skeleton code from zyBooks
void TickFct_Lights()
{
  switch(LA_State) {   // Transitions
     case LA_SMStart:  // Initial transition
        LA_State = LA_s0;
        break;

     case LA_s0:
        if (!A0) {
           LA_State = LA_s0;
        }
        else if (A0) {
           LA_State = LA_s1;
        }
        break;

     case LA_s1:
        if (!A0) {
           LA_State = LA_s0;
        }
        else if (A0) {
           LA_State = LA_s1;
        }
        break;

     default:
        LA_State = LA_SMStart;
        break;
  } // Transitions

  switch(LA_State) {   // State actions
     case LA_s0:
        break;

     case LA_s1:
        B0 = A1;
        break;

     default:
        break;
   } // State actions
}

int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;

	unsigned char button;	
	unsigned char output = 0x00;
    /* Insert your solution below */
    while (1) 
    {
	button = ~PINA;
	output = 0x00;

    }
    return 1;
}
