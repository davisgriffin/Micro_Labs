
// Title

#ifndef INTERRUPTS_H
#define INTERRUPTS_H

// Interrupt Pins
#define _bit_EINT3 17
#define _bit_EINT2 16
#define _bit_EINT1 15
#define _bit_EINT0 14

// Functions

/* Interrupt_Init_JoystickDown
 * Initialize the down switch of the joystick to be interrupt driven like a
 * slot lever.
 * * NOTE this uses EINT3 for the ISR
 * ------------------------------------------
 * Parameters: ISR
 * - address of the ISR
 */
void Interrupt_Init_JoystickDown(unsigned int ISR);

/* Interrupt_Init_JoystickPress
 * Initialize the center press of the joystick to be interrupt driven for game
 * switches.
 * * NOTE this uses EINT0 for the ISR
 * ------------------------------------------
 * Parameters: ISR
 * - address of the ISR
 */
void Interrupt_Init_JoystickPress(unsigned int ISR);

/* Interrupt_Init_PushButton
 * Initialize the pushbutton to be interrupt driven for point refills.
 * * NOTE this uses EINT1 for the ISR
 * ------------------------------------------
 * Parameters: ISR
 * - address of the ISR
 */
void Interrupt_Init_PushButton(unsigned int ISR);

#endif
