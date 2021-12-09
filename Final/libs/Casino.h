
/**
 * Casino header file. This contains the costs and bonuses of each game along
 * with each of the games initialization and running functions. Reference
 * Davis_Haney_Final on how to set up your own casino.
 * @authors Griffin Davis and Sydnee Haney
 */

#ifndef CASINO_H
#define CASINO_H

// Constants
#define _slots_winBonus 100
#define _slots_hugeWinBonus 200
#define _slots_cost 10
#define _wheel_winBonus 50
#define _wheel_hugeWinBonus 75
#define _wheel_loseCost 50
#define _blackjack_cost 20

/* GameSelect
 * Displays options for playing slots, wheel of fortune, or blackjack
 */
void GameSelect(void);

/* BlackJack_Init
 * Displays blackjack welcome message and points.
 */
void BlackJack_Init(int points);

/* RunBlackJack
 * Runs a simulation of playing blackjack on the LCD screen using the lever to
 * "hit" and the push button to "stand".
 * ------------------------------------------
 * Parameters:
 * points :: int*
 * - Pointer to the user's points
 * plyrSum :: int*
 * - Pointer to the sum total of the player's hand
 * dlrSum :: int*
 * - Pointer to the sum total of the dealer's hand
 * dlrDown :: int*
 * - Pointer to the card the dealer is not showing
 * turn :: int
 * - How many turns have occurred in the game
 */
int RunBlackJack(int* points, int* plyrSum, int* dlrSum, int* dlrDown, int turn);

/* RunSlots
 * Runs the slot machine game using the on-board LCD
 */
void RunSlots(int* points);

/* Slots_Init
 * Create the necssary characters in LCD CGRAM for the game and display play
 * message
 */
void Slots_Init(int points);

/* RunWheel
 * Uses the step motor to simulate wheel of fortune
 * ------------------------------------------
 * Parameters:
 * currentStep :: int
 * - Current step of the motor (0-4) to determine which value was hit
 * points :: int*
 * - Pointer to the user's points
 */
int RunWheel(int currentStep, int* points);

/* Wheel_Init
 * Displays the WHEEL OF FORTUNE with the user's points
 */
void Wheel_Init(int points);

#endif
