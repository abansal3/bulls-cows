/* This is the console executable that makes use of the BullCow Class. This acts as the view in a MVC Pattern and is reponsible for all user interaction. For game logic, see the FBullCowGame Class.
*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetGuess();
bool AskToPlayAgain();
void ShowGameSummary();

FBullCowGame BCGame;

int main() {

    bool PlayAgain = false;
    
    do {
        PrintIntro();
        PlayGame();
        PlayAgain = AskToPlayAgain();
    } while (PlayAgain);

    return 0;
}

// Introduce the game
void PrintIntro() {
    std::cout << "\nWelcome to Bulls & Cows.\n";
    std::cout << "Guess the " << BCGame.GetHiddenWordLength() << " letter word.\n";
    return;
}

// Get the player input
FText GetValidGuess() {
    FText Guess;
    EGuessStatus Status = EGuessStatus::Not_Valid;

    do {
        int32 CurrentTry = BCGame.GetCurrentTry();

        std::cout << "\nTry " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
        
        getline(std::cin, Guess);

        Status = BCGame.CheckGuessValidity(Guess);
        
        switch (Status) {
            case EGuessStatus::Wrong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word with no repeating letters.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please enter the word in lowercase.\n";
                break;
            default:
                break;
        }
    } while (Status != EGuessStatus::OK);

    return Guess;
}

void ShowGameSummary() {
    // Game won
    if (BCGame.IsGameWon()) {
        std::cout << "\nCongratulations! You've won the game.\n\n";
    } else { // Game lost
        std::cout << "\nBetter luck next time.\n\n";
    }
}

void PlayGame() {
    BCGame.Reset();

    int32 MaxTries = BCGame.GetMaxTries();

    while (!BCGame.IsGameWon() && (BCGame.GetCurrentTry() <= MaxTries)) {
        FText Guess = GetValidGuess();

        // Submit valid guess to the game
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

        // Print number of bulls and cows
        std::cout << "Bulls = " << BullCowCount.Bulls << std::endl;
        std::cout << "Cows = " << BullCowCount.Cows << std::endl;
    }

    ShowGameSummary();

    return;
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again? (y/n): ";
    FText Response;
    getline(std::cin, Response);
    
    if (Response[0] == 'y' || Response[0] == 'Y') {
        return true;
    } else if (Response[0] == 'n' || Response[0] == 'N') {
        return false;
    }

    return false;
}
