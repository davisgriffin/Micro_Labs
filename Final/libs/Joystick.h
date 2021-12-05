
// Title

#ifndef JOYSTICK_H
#define JOYSTICK_H

// Joystick Pins
#define _up_pin 1 << 17
#define _down_pin 1 << 20
#define _left_pin 1 << 19
#define _right_pin 1 << 18
#define _pushdown 1 << 16
#define _all_directions_no_push 1<<17 | 1<<18 | 1<<19 | 1<<20
#define _all_directions_and_push 1<<16 | 1<<17 | 1<<18 | 1<<19 | 1<<20

// Functions

/* Joystick_Init
 * Set the given joystick pins to general purpose inputs
 * ------------------------------------------
 * Parameters: pinMask
 * - pins to be established as inputs
 */
void Joystick_Init(unsigned int pinMask);

/* Joystick_Interrupt_Down_Init
 * Initialize the down switch of the joystick to be interrupt driven like a
 * slot lever.
 * * NOTE this uses EINT3 for the ISR
 * ------------------------------------------
 * Parameters: ISR
 * - address of the ISR
 */
void Joystick_Interrupt_Down_Init(unsigned int ISR);

#endif
