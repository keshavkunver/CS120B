/*	Author: lab
 *  Partner(s) Name: Keshav Kunver
 *	Lab Section:
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

volatile unsigned char TimerFlag = 0; // TimerISR() sets this to 1. C programmer should clear to 0.

// Internal variables for mapping AVR's ISR to our cleaner TimerISR model.
unsigned long _avr_timer_M = 1; // Start count from here, down to 0. Default 1ms.
unsigned long _avr_timer_cntcurr = 0; // Current internal count of 1ms ticks


unsigned char button;
enum Light_States { Start, B_zero, B_one, B_two, Button_Press } state;

// These settings can be changed to create a timer with a different granularity than 
// the 1ms described here. There are also 3 other timers (1 16-bit, 2 8-bit) on the
// atmega1284 that can be used. Look in the data sheet to see how we got to these 
// values.
void TimerOn() {
    // AVR timer/counter controller register TCCR1
    TCCR1B = 0x0B; // 0000_1011 (0x0B)
                   // bit3=1; CTC mode (clear itmer on compare)
                   // bit[2:0]=011 - pre-scalar 64
                   // 8MHz clock (assuming CLKDIV8 fuse cleared)
                   // => 8,000,000 ticks/second
                   // 8,000,000 / 64 = 125,000 ticks/second (from pre-scalar)
                   // TCNT1 register will count up 125,000 times per second
                   // We want 1,000 ticks/second (1ms)
    OCR1A = 125; // Set the Output Compare Register 1A (OCR1A) to 125
                 // Whenever TCNT1 == OCR1A we clear (CTC)
                 // => 125,000 ticks/second / 125 = 1,000 ticks/second (1ms)
    // AVR timer interrupt mask register
    TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt
    // Initialize the AVR counter (referenced in description above)
    TCNT1 = 0;
    // The TimerISR will be called every _avr_timer_cntcurr milliseconds
    _avr_timer_cntcurr = _avr_timer_M;
    // Enable global interrupts on the System REGister
    SREG |= 0x80;
}

void TimerOff() {
    TCCR1B = 0x00; // bit[3:0]=0000 - timer off
}

void TimerISR() {
    TimerFlag = 1;
}

// In our disciplined approach, the C programmer does not touch this ISR, 
// but rather the TimerISR() abstraction.
// ISR: Interrupt Service Routine
// TIMER1_COMPA_vect: Pre-defined interrupt vector
ISR(TIMER1_COMPA_vect) {
    // CPU automatically calls when TCNT1==OCR1A (every 1ms per TimerOn settings)
    --_avr_timer_cntcurr; // Count down to 0 rather than up to TOP
    if (_avr_timer_cntcurr == 0) { // Results in a more efficient compare
        TimerISR(); // Call the ISR abstraction that the programmer interfaces with
        _avr_timer_cntcurr = _avr_timer_M;
    }
}

// Set TimerISR() to tick every M ms
// Whenever dealing with time use 'long' to avoid issues of overflow
void TimerSet(unsigned long M) {
    _avr_timer_M = M;
    _avr_timer_cntcurr = _avr_timer_M;
}

void Light_Game()
{
	switch(state)	//Transitions
	{
		case Start:
			state = B_zero;
			break;
		case B_zero:
			state = B_one;
			break;
		case B_one:
			state = button ? Button_Press : B_two;
			break;
		case B_two:
			state = B_one;
			break;
		case Button_Press:
			state = button ? Button_Press : B_zero;
			break;
		default:
			state = Start;
			break;
	}

	switch(state)	//State actions
	{
		case Start:
			PORTB = 0x00;
			break;
		case B_zero:
			PORTB = 0x01;
			break;
		case B_one:
			PORTB = 0x02;
			break;
		case B_two:
			PORTB = 0x04;
			break;
		case Button_Press:
			PORTB = 0x02;
			break;
		default:
			break;
	}
}

int main(void) 
{
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;	DDRA = 0xFF;
	DDRB = 0xFF;	DDRB = 0x00;

	TimerSet(300);
	TimerOn();
	
    /* Insert your solution below */
    while (1) 
    {
	button = ~PINA & 0x01;

	//one tick
	Light_Game();

	//wait for period
	while(!TimerFlag);
	TimerFlag = 0;
		
    }
    return 1;
}
