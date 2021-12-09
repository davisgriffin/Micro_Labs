
/**
 * Timer source file. This contains functions required to use synchronous delays
 * in source code.
 * @authors Griffin Davis and Sydnee Haney
 */

#include "LPC214x.h"

void delayUs(unsigned int delayInus) {
  T1TCR = 0x02;          				// Stop and reset timer
  T1PR  = 0x00;							// Set prescaler to zero
  T1MR0 = delayInus * 15;				// Based upon Pclk = 15 MHz.
  T1IR  = 0xff;							// Reset all the interrupt flags
  T1MCR = 0x04;							// Stop the timer on a match
  T1TCR = 0x01;							// Start the timer now
  
  while (T1TCR & 0x01);
}

void delayMs(unsigned int delayInms) {
    delayUs(delayInms * 1000);
}
