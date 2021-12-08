
// Title

#ifndef CASINO_H
#define CASINO_H

/* RunSlots
 * Runs the slot machine game using the on-board LCD
 */
void RunSlots(int* points);

/* Slots_Init
 * Create the necssary characters in LCD CGRAM for the game and display play
 * message
 */
void Slots_Init(int points);

int RunWheel(int currentStep, int* points);

#endif
