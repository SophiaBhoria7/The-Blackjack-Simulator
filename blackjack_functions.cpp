// Programmer: Sophia Bhoria
// Date: 10/07/2024
// Purpose: Defines the game logic and helper functions for Blackjack simulation.

#include <iomanip>  // Include the header for input/output manipulators (like setprecision)
#include <cstdlib>  // Include the header for standard library functions (like rand)
#include "blackjack_simulator.h"  // Include the header file for Blackjack simulator functions
#include <iostream>  // Include the header for input/output operations
#include <string>  // Include the header for string manipulation

using namespace std;  // Use the standard namespace

// Function to generate a random card value between MIN_CARD and MAX_CARD (inclusive)
int generateRandomCard() {
    return rand() % (MAX_CARD - MIN_CARD + 1) + MIN_CARD;
}

// Function to check if the initial two cards form a Blackjack
bool isBlackjack(int card1, int card2) {
    // Blackjack occurs if either card is an Ace (value 1) and the other is a 10 or face card (11, 12, 13)
    return (card1 == 1 && (card2 == 10 || card2 >= 11)) || (card2 == 1 && (card1 == 10 || card1 >= 11));
}

// Function to calculate the total hand value, taking into account the Ace's flexible value
int calculateHandTotal(int card1, int card2, bool hasAce) {
    int total = 0;  // Initialize the total hand value
    // If the hand has an Ace, start by assuming its value is 11
    if (hasAce) {
        total += 11;
        // If the other card is a 10 or face card, the Ace's value should be 1
        if (card2 >= 11) total += 10; else total += card2;
    } else {
        // If there's no Ace, calculate the sum of the two cards normally
        if (card1 >= 11) total += 10; else total += card1;
        if (card2 >= 11) total += 10; else total += card2;
    }
    return total;  // Return the calculated total
}

// Function to calculate the total hand value after adding a new card
int calculateTotal(int total, int newCard) {
    // If the new card is an Ace and the current total is less than or equal to 10, treat the Ace as 11
    if (newCard == 1 && total <= 10) {
        return total + 11;
    } else if (newCard >= 11) {
        // If the new card is a 10 or face card, add 10 to the total
        return total + 10;
    } else {
        // Otherwise, add the new card's face value to the total
        return total + newCard;
    }
}

// Function to update the player's balance based on the outcome of the round
void updatePlayerBalance(double &balance, double wager, bool playerWins, bool isBlackjack) {
    if (playerWins) {
        // If the player wins, add the wager to their balance
        if (isBlackjack) {
            // If it was a Blackjack, the player gets 1.5 times their wager
            balance += (wager * 1.5);
        } else {
            // Otherwise, the player gets their wager back
            balance += wager;
        }
    } else {
        // If the player loses, subtract the wager from their balance
        balance -= wager;
    }
}

// Function to display the outcome of the round (win, loss, Blackjack) and the current balance
void displayOutcome(bool playerWins, bool isBlackjack, double &balance, double wager) {
    if (playerWins) {
        // If the player wins, display a winning message
        if (isBlackjack) {
            cout << "Player won with a Blackjack! ";
        } else {
            cout << "Player won this round! ";
        }
        // Display the winnings amount
        cout << "Winnings: $" << (isBlackjack ? (wager * 1.5) : wager) << endl;
    } else {
        // If the player loses, display a losing message
        cout << "Player lost this round. Wager: $" << wager << endl;
    }
    // Display the updated balance
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
}

// Function to display a summary of the game at the end
void displayGameSummary(int totalRounds, int totalWins, int totalLosses, int totalBlackjacks, double finalBalance) {
    cout << "\nGame Summary:\n";
    cout << "Total Rounds Played: " << totalRounds << endl;
    cout << "Total Wins: " << totalWins << endl;
    cout << "Total Losses: " << totalLosses << endl;
    cout << "Total Blackjacks: " << totalBlackjacks << endl;
    cout << "Final Balance: $" << fixed << setprecision(2) << finalBalance << endl;
}

// Function to get the name of a card based on its value
string getCardName(int card) {
    switch (card) {
        case 1: return "Ace";
        case 11: return "Jack";
        case 12: return "Queen";
        case 13: return "King";
        default: return to_string(card);
    }
}

// Function to get the name of a random suit
string getSuitName() {
    // Generate a random suit index (0-3)
    int suit = rand() % 4;
    switch (suit) {
        case 0: return "Hearts";
        case 1: return "Diamonds";
        case 2: return "Clubs";
        case 3: return "Spades";
        default: return "Unknown";
    }
}
