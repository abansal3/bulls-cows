#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const {
    return GameWon;
}

void FBullCowGame::Reset() {
    MyCurrentTry = 1;
    
    const FString HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;

    GameWon = false;
    
    return;
}

int32 FBullCowGame::GetMaxTries() const {
    TMap<int32,int32> WordLengthToMaxTries = {{3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20}};
    return WordLengthToMaxTries[GetHiddenWordLength()]; 
}

// Receives a valid guess, increments try and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
    MyCurrentTry++;
    FBullCowCount BullCowCount;

    // Loop through all letters in the hidden word
    int32 WordLength = MyHiddenWord.length(); // Assuming same length of hidden word and guess word
    for (int32 MHWCharIndex=0; MHWCharIndex<WordLength; MHWCharIndex++) {
        // Compare letters against guess
        for (int32 GCharIndex=0; GCharIndex<WordLength; GCharIndex++) {
            // If they match
            if (Guess[GCharIndex] == MyHiddenWord[MHWCharIndex]) {
                // If they're in the same place
                if (MHWCharIndex == GCharIndex) {
                    // Increment bulls
                    BullCowCount.Bulls++; 
                } // If they're not
                else {
                    // Increment cows
                    BullCowCount.Cows++;
                }
            }
        }
    }

    if (BullCowCount.Bulls == WordLength) {
        GameWon = true;
    } else {
        GameWon = false;
    }
    
    return BullCowCount;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    // isogram check
    if (!IsIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    }
    // lowercase check
    else if (!IsLowercase(Guess)) {
        return EGuessStatus::Not_Lowercase;
    }
    // length check
    else if (Guess.length() != GetHiddenWordLength()) {
        return EGuessStatus::Wrong_Length;
    }
    // all good
    else {
        return EGuessStatus::OK;
    }
}

bool FBullCowGame::IsIsogram(FString Guess) const {

    if (Guess.length() <= 1) { return true; }

    TMap<char, bool> LettersSeen;
    for (auto Letter : Guess) {
        Letter = tolower(Letter);

        if (!LettersSeen[Letter]) {
            LettersSeen[Letter] = true;
        } else {
            return false;
        }
    }
    return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const {
    for (auto Letter : Guess) {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
}