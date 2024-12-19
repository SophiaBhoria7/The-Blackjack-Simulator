// Programmer: Sophia Bhoria
// Date: 10/07/2024
// Purpose: Declare the functions, constants, and any shared definitions used across multiple source files, enabling code modularity and reusability without redefining the same items in each file

#ifndef BLACKJACK_SIMULATOR_H
#define BLACKJACK_SIMULATOR_H

#include <string>  // Include the header for string manipulation

// Define constants for card values and the range for random balance
const int MIN_CARD = 1;  // Minimum card value (Ace)
const int MAX_CARD = 13;  // Maximum card value (King)
const double MIN_BALANCE = 12.00;  // Minimum starting balance for the player
const double MAX_BALANCE = 7000.00;  // Maximum starting balance for the player

// Function Prototypes (forward declarations)

// Function to generate a random card value between MIN_CARD and MAX_CARD (inclusive)
int generateRandomCard();

// Function to check if the initial two cards form a Blackjack
bool isBlackjack(int card1, int card2);

// Function to calculate the total hand value, taking into account the Ace's flexible value
int calculateHandTotal(int card1, int card2, bool hasAce);

// Function to calculate the total hand value after adding a new card
int calculateTotal(int total, int newCard);

// Function to update the player's balance based on the outcome of the round
void updatePlayerBalance(double &balance, double wager, bool playerWins, bool isBlackjack);

// Function to display the outcome of the round (win, loss, Blackjack) and the current balance
void displayOutcome(bool playerWins, bool isBlackjack, double &balance, double wager);

// Function to display a summary of the game at the end
void displayGameSummary(int totalRounds, int totalWins, int totalLosses, int totalBlackjacks, double finalBalance);

// Function to get the name of a card based on its value
std::string getCardName(int card);

// Function to get the name of a random suit
std::string getSuitName();

#endif
