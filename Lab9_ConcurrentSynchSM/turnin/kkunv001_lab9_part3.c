/*	Author: lab
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #9  Exercise #3
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

enum ThreeLED {Continue} state_Three;
enum BlinkLED {On_Off} state_Blink;
enum ComboLED {Combine} state_Combo;
enum Speaker {Init, On} state_Speaker;

unsigned char i = 0;
unsigned char led = 0x00;
unsigned char on_off = 1;

unsigned char speaker = 0;
unsigned char button;

//ThreeLEDsSM function
void Three_Tick()
{
	switch(state_Three) {	//Transitions
		case Continue:
			state_Three = Continue;
			break;
		default:
			break;
	}

	switch(state_Three) {	//Actions
		case Continue:
			if(i == 0) {
				led = 0x01;
				i++;
			}
			else if(i == 1) {
				led = 0x02;
				i++;
			}
			else if(i == 2) {
				led = 0x04;
				i = 0;
			}
			break;
		default:
			break;
	}
	
}

//BlinkingLEDSM function
void Blink_Tick()
{
	switch(state_Blink) {	//Transitions
		case On_Off:
			state_Blink = On_Off;
			break;
		default:
			break;
	}

	switch(state_Blink) {	//Actions
		case On_Off:
			on_off = ~on_off;
			break;
		default:
			break;
	}

}
//CombineLEDsSM function
void Combo_Tick()
{
	switch(state_Combo) {	//Transitions
		case Combine:
			state_Combo = Combine;
			break;
		default:
			break;
	}

	switch(state_Combo) {	//Actions
		case Combine:
			PORTB = ( ( (speaker & 0x01) << 4) | ( (on_off & 0x01) << 3) | led);
			break;
		default:
			break;
	}

}

void Speaker_Tick()
{
	switch(state_Speaker) {	//Transitions
		case Init:
			if(button) {
				state_Speaker = On;
			}
			else {
				state_Speaker = Init;
			}
			break;
		case On:
			if(button) {
				state_Speaker = On;
			}
			else {
				state_Speaker = Init;
			}
		default:
			break;
	}

	switch(state_Speaker) {	//Actions
		case Init:
			speaker = 0;
			break;
		case On:
			speaker = 1;
			break;
		default:
			break;
	}
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	PORTA = 0xFF;
	DDRB = 0xFF;	PORTB = 0x00;

	unsigned long threePeriod = 300;
	unsigned long blinkPeriod = 1000;

	unsigned char speakerPeriod = 2;
	button = ~PINA & 0x01;

	TimerSet(2);	//GCD(1000,300,2) = 2
	TimerOn();

	state_Three = Continue;
	state_Blink = On_Off;
	state_Combo = Combine;

    /* Insert your solution below */
    while (1) {
	
	if(threePeriod >= 300) {
		Three_Tick();
		threePeriod = 0;
	}
	
	if(blinkPeriod >= 1000) {
		Blink_Tick();
		blinkPeriod = 0;
	}

	if(speakerPeriod >= 2) {
		Speaker_Tick();
		speakerPeriod = 0;
	}

	Combo_Tick();

	while(!TimerFlag) {}
	TimerFlag = 0;

	//update periods
	threePeriod += 2;
	blinkPeriod += 2;
	
	speakerPeriod += 2;	
	
    }
    return 1;
}
