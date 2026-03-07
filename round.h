#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <Windows.h>
#include "layout.h"
#include "layoutView.h"
#include "stock.h"
#include "hand.h"
#include "round.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "Tournament.h"


using namespace std;

// Forward declaration for circular dependency
//class Round;

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
    std::string getEngine() const;
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


    //-------------------------------------------
    void initialize(Player* players[2], Tournament& tournament);

    void play(Player* players[2]);

    //Player* determineWinner(Player* players[2]);

    void firstTurn();
    string obtainEngine();
    void tiePoints(Player* Human, Player* Computer, Tournament& gameTournament);
    void addTotalPoints(Player& winner, Player& loser, Tournament& gameTournament);
    bool applyMove(Player* player, Player::Move move);


    bool checkHandForTile(Player* p, string target);
    string showLoadMenu();
    int menu();

    /*void play(Player* p[2])
    {
        players = p;

        // now both classes refer to same players
    } */

    Round(Player* p[2])
    {
        players[0] = p[0];
        players[1] = p[1];
    }

private:

    //this is a pointer to an already existed array of pointers
    //this is used so there are no copies of the players
    Player* players[2];

    // --- 7. Variables ---
    int roundNum;
    int engineIndex;
    int currentPlayer;
    int nextPlayer;
    bool roundOverFlag;
    std::string engine;
    std::string requiredEngine;
    string engine;

    //class Variables
    Layout layout;
    Stock gameStock;
    LayoutView gameView;

    // Array tracking individual pass status for both players (0: Human, 1: Computer)
    std::array<bool, 2> passed;

    // The list of possible engines in descending order
    std::vector<std::string> requiredEngines;

    //-------------------------------------------

    Layout layout;
    Stock stock;

    int currentPlayer;
    int nextPlayer;

    bool roundEnded;


};