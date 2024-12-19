// Programmer: Sophia Bhoria
// Date: 10/07/2024
// Purpose: This program simulates a simplified Blackjack game between a player and a dealer.
//          It includes features such as wagering, hitting, standing, and Blackjack detection.

#include <iostream>  // Include the header for input/output operations
#include <cstdlib>  // Include the header for standard library functions (like rand)
#include <ctime>  // Include the header for time-related functions
#include <iomanip>  // Include the header for input/output manipulators (like setprecision)
#include "blackjack_simulator.h"  // Include the header file for Blackjack simulator functions

using namespace std;  // Use the standard namespace

int main() {
    srand(5300); // Seed the random number generator (using a fixed seed for consistent results)

    string playerName;  // Variable to store the player's name
    double balance = 0;  // Variable to store the player's balance
    double wager = 0;  // Variable to store the player's wager for each round
    int totalRounds = 0, totalWins = 0, totalLosses = 0, totalBlackjacks = 0;  // Variables to track game statistics

    // Prompt for player name and generate starting balance
    cout << "Welcome to CodeJack: The Blackjack Simulator!\n";
    cout << "Player, please enter your name: ";
    cin >> playerName;

    // Random starting balance between $12.00 and $7000.00
    balance = MIN_BALANCE + (rand() % static_cast<int>(MAX_BALANCE - MIN_BALANCE + 1)) + (rand() % 100 / 100.0);
    cout << fixed << setprecision(2);
    cout << "Hi " << playerName << ", I’m pleased to notify you that your starting balance is $" << balance << ".\n";

    char playAgain = 'Y';  // Variable to control the game loop, initially set to 'Y' to start the game

    while (playAgain == 'Y' && balance > 0) {  // Continue playing as long as the player wants and has balance
        totalRounds++;  // Increment the total number of rounds played
        cout << "\nRound " << totalRounds << "\n*******\n";
        cout << "Player balance: $" << balance << endl;

        // Get valid wager from player (ensure wager is within the balance and positive)
        do {
            cout << "Please enter your wager: $";
            cin >> wager;
        } while (wager > balance || wager <= 0);

        // Deal cards (generating random values for player and dealer)
        int playerCard1 = generateRandomCard();
        int playerCard2 = generateRandomCard();
        int dealerCard1 = generateRandomCard();
        int dealerCard2 = generateRandomCard();

        cout << "Player Hand: " << getCardName(playerCard1) << " of " << getSuitName() 
             << ", " << getCardName(playerCard2) << " of " << getSuitName() << endl;
        cout << "Dealer’s Hand: " << getCardName(dealerCard1) << " of " << getSuitName() << ", [Hidden Card]" << endl;

        int playerTotal = calculateHandTotal(playerCard1, playerCard2, playerCard1 == 1 || playerCard2 == 1);
        int dealerTotal = calculateHandTotal(dealerCard1, dealerCard2, dealerCard1 == 1 || dealerCard2 == 1);

        // Check for Blackjack (both player and dealer)
        bool playerHasBlackjack = isBlackjack(playerCard1, playerCard2);
        bool dealerHasBlackjack = isBlackjack(dealerCard1, dealerCard2);

        if (playerHasBlackjack || dealerHasBlackjack) {
            if (playerHasBlackjack && dealerHasBlackjack) {
                cout << "It’s a tie, both have Blackjack!\n";
            } else if (playerHasBlackjack) {
                cout << "Congratulations, player! You have Blackjack!\n";
                totalWins++;  // Increment the number of player wins
                totalBlackjacks++;  // Increment the number of Blackjacks
                updatePlayerBalance(balance, wager, true, true);  // Update balance for a Blackjack win
            } else {
                cout << "Sorry, dealer hit Blackjack.\n";
                totalLosses++;  // Increment the number of player losses
                updatePlayerBalance(balance, wager, false, false);  // Update balance for a Blackjack loss
            }
        } else {
            // Player's turn
            char action;
            bool firstAction = true;  // Flag to track if it's the player's first action
            do {
                if (firstAction) {
                    cout << "Player, please choose your action: Hit(H), Stand(S), Double Down(D): ";
                } else {
                    cout << "Player, please choose your action: Hit(H), Stand(S): ";
                }
                cin >> action;

                if (action == 'H') {
                    int newCard = generateRandomCard();
                    cout << "Player Hand: " << getCardName(newCard) << " of " << getSuitName() << endl;
                    playerTotal = calculateTotal(playerTotal, newCard);  // Update player total after hitting
                    cout << "Player Total: " << playerTotal << endl;
                    if (playerTotal > 21) {
                        cout << "You busted! Player loses this round.\n";
                        totalLosses++;
                        updatePlayerBalance(balance, wager, false, false);  // Update balance for a bust
                        break;  // Exit the player's turn loop if they bust
                    }
                } else if (firstAction && action == 'D') {
                    cout << "Player chose Double Down!" << endl;
                    int newCard = generateRandomCard();
                    cout << "Player Hand: " << getCardName(newCard) << " of " << getSuitName() << endl;
                    playerTotal = calculateTotal(playerTotal, newCard);  // Update player total after doubling down
                    wager *= 2;  // Double the wager
                    cout << "Player Total: " << playerTotal << endl;
                    if (playerTotal > 21) {
                        cout << "You busted with Double Down! Player loses this round.\n";
                        totalLosses++;
                        updatePlayerBalance(balance, wager, false, false);  // Update balance for a bust with double down
                        break;  // Exit the player's turn loop if they bust with double down
                    }
                    break;  // Exit the player's turn loop after doubling down
                }

                firstAction = false;  // Set the flag to false after the first action
            } while (action != 'S' && playerTotal <= 21);  // Continue the player's turn loop until they stand or bust

            // Dealer's turn if player hasn't busted
            if (playerTotal <= 21) {
                cout << "Dealer's Hand: " << getCardName(dealerCard1) << " of " << getSuitName() 
                     << ", " << getCardName(dealerCard2) << " of " << getSuitName() << endl;
                cout << "Dealer’s Total: " << dealerTotal << endl;

                while (dealerTotal < 17) {  // Dealer hits until their total is 17 or more
                    int newCard = generateRandomCard();
                    dealerTotal = calculateTotal(dealerTotal, newCard);  // Update dealer total after hitting
                    cout << "Dealer hits and draws " << getCardName(newCard) << " of " << getSuitName() << endl;
                    cout << "Dealer’s Total: " << dealerTotal << endl;
                }

                if (dealerTotal > 21 || playerTotal > dealerTotal) {  // Player wins if dealer busts or player has a higher total
                    cout << "Congratulations! You win this round!\n";
                    totalWins++;
                    updatePlayerBalance(balance, wager, true, false);  // Update balance for a win
                } else if (playerTotal < dealerTotal) {  // Player loses if dealer has a higher total
                    cout << "Sorry, you lose this round.\n";
                    totalLosses++;
                    updatePlayerBalance(balance, wager, false, false);  // Update balance for a loss
                } else {  // It's a tie if both player and dealer have the same total
                    cout << "It's a tie!\n";
                }
            }
        }

        cout << "Balance Update: $" << fixed << setprecision(2) << balance << endl;

        if (balance > 0) {  // Ask the player if they want to play another round if they have balance left
            cout << "Play another round? (Y/N): ";
            cin >> playAgain;
        } else {  // End the game if the player runs out of balance
            cout << "You are out of balance.\n";
            break;
        }
    }

    displayGameSummary(totalRounds, totalWins, totalLosses, totalBlackjacks, balance);  // Display the game summary

    return 0;  // Indicate successful program execution
}
