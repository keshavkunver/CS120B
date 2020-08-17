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

enum Light_States { Start, Init, Inc, Inc_Wait, Dec, Dec_Wait, Off  } state;

//unsigned char button1;
//unsigned char button2;

//skeleton code from zyBooks
void TickFct_Lights()
{
  switch(state)  // Transitions
  {   
	case Start:
        	state = Init;
        	break;

     	case Init:
        	if( PINA & 0x01 ) {
			state = Inc;
		}
        	else if( PINA & 0x02 ) {
			state = Dec;
		}
		else if ( PINA & 0x03 ) {
			state = Off;
		}
		break;

	case Inc:
		state = Inc_Wait;
	
	case Inc_Wait:
		if(PINA & 0x01) {
			state = Inc_Wait;
		}
		else if(PINA & 0x03) {
			state = Off;
		}
		else if(PINA == 0x00) {
			state = Init;
		}
		break;

	case Dec:
		state = Dec_Wait;
		break;

	case Dec_Wait:
		if(PINA & 0x02) {
			state = Dec_Wait;
		}
		else if(PINA & 0x03) {
			state = Off;
		}
		else if(PINA == 0x00) {
			state = Init;
		}
		break; 
	

	case Off:
		if( PINA == 0x00 ) {
			state = Init;
		}
		else {
			state = Off;
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
		break;
	
	case Inc:
		if(PORTC >= 0x09){
			PORTC = 0x09;
		}
		else {
			PORTC += 0x01;
		}
		break;

	case Inc_Wait:
		break;

	case Dec:
		if(PORTC <= 0x00) {
			PORTC = 0x00;
		}
		else {
			PORTC -= 0x01;
		}
		break;
	
	case Dec_Wait:
		break;

	case Off:
		PORTC = 0x00;
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
	PORTC = 0x07;
	//button1 = ~PINA & 0x01;
    	//button2 = ~PINA & 0x02;

    /* Insert your solution below */
    while (1) 
    {
	TickFct_Lights();
    }
    return 1;
}
