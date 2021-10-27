#include <LPC214x.H>

/**
 * ECE5450 Lab 2 Exercise 1
 * This program will display LEDs blinking from left-to-right and then right-to-
 * left using P0.8-P0.15.
 * NOTE: LEDs are tied to VCC and IO, so a high IO leads to an extinguished LED
 * due to an open circuit. No current will flow unless the pin is low.
 * @authors Griffin Davis, Sydnee Haney
 */
void wait (void) {
    int d;

    for(d=0; d<2500000; d++);
}

int main (void) {
    unsigned int mask = 0x00008000;
    unsigned int dir = 0;
    IODIR0 = 0x0000FF00;
    IOSET0 = 0x0000FF00;

	while(1){
        IOCLR0 = mask;
        wait();
        IOSET0 = mask;
        
        if (dir) mask = mask << 1;
        else mask = mask >> 1;

        if( (mask & 0x00008000) || (mask & 0x00000100)) dir = !dir;
	}
}
