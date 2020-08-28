/*
 *	Hello World Program
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "io.h"
#endif



int main(void) 
{
	DDRC = 0xFF;	PORTC = 0x00;
	DDRD = 0xFF;	PORTD = 0x00;

	//Initializes Display
	LCD_init();

	//Outputs desired string
	LCD_DisplayString(1, "Hello World!");
    
    while (1) 
    {

    }
    return 1;
}
