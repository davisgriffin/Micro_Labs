
/**
 * Timer source file. This contains functions required to use synchronous delays
 * in source code.
 * @authors Griffin Davis and Sydnee Haney
 */

#ifndef TIMER_H
#define TIMER_H

/* delayUs
 * Delays for the given time in microseconds.
 * ------------------------------------------
 * Paramaters: delayInus
 *  - Time in microseconds
 */
void delayUs(unsigned int delayInus);

/* delayMs
 * Delays for the given time in milliseconds.
 * ------------------------------------------
 * Paramaters: delayInms
 *  - Time in milliseconds
 */
void delayMs(unsigned int delayInms);

#endif
