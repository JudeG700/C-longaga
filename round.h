#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>
#include "player.h"

// Forward declaration for circular dependency
class Round;

/* *********************************************************************
Class Name: Round
Purpose: Manages the lifecycle of a single game round, including engine
         tracking, turn order, passing status, and win conditions.
********************************************************************* */
class Round {

public:
    // --- 2. Constructors ---
    Round();

    // --- 3. Destructor ---
    virtual ~Round() {}

    // --- 4. Selectors ---
    bool isRoundOver() const;
    int getRoundNum() const;
    //std::string getEngine() const;
    std::string getRequiredEngine() const;
    int getCurrentPlayer() const;
    int getNextPlayer() const;
    bool bothPassed() const;
    bool isPassed(int playerIndex) const;
    std::string yesNo(bool stateValue) const;

    // --- 5. Mutators ---
    void roundOver();
    void nextRound();
    void setRoundNum(int roundNumber);
    void setCurrentPlayer(int playerIndex);
    void setNextPlayer(int playerIndex);
    void setPassed(int playerIndex);
    void resetPass(int playerIndex);
    void resetPasses();

    // --- 6. Utility Functions ---
    void determineRequiredEngine();
    std::string determineEngine(const std::vector<std::string>& playerHand);
    Player* checkWinner(Player* humanPlayer, Player* computerPlayer);
    void incEIndex();

private:
    // --- 7. Variables ---
    int roundNum;
    int engineIndex;
    int currentPlayer;
    int nextPlayer;
    bool roundOverFlag;
    std::string engine;
    std::string requiredEngine;

    // Array tracking individual pass status for both players (0: Human, 1: Computer)
    std::array<bool, 2> passed;

    // The list of possible engines in descending order
    std::vector<std::string> requiredEngines;

};