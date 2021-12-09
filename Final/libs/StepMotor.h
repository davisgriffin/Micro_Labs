
/**
 * Step motor header file. This contains many of the functions and pins required
 * to efficiently drive the step motor on board the LPC2148 education board.
 * @authors Griffin Davis and Sydnee Haney
 */

#ifndef STEPMOTOR_H
#define STEPMOTOR_H

// Motor Pins
#define _fwd_phase 1 << 12
#define _rev_phase 1 << 21
#define _stepDelay_ms 10

// Functions

/* Step_Init
 * Initialize the step motor pins.
 */
void Step_Init(void);

/* Step_Forward
 * Move the motor forward by a given number of steps.
 * ------------------------------------------
 * Parameters:
 * currentStep :: unsigned int
 * - Step the motor is on presently.
 * steps :: unsigned int
 * - Number of steps to move.
 * 
 * Returns: The current step.
 */
int Step_Forward(unsigned int currentStep, unsigned int steps);

#endif
