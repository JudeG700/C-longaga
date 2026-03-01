/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

#include "round.h"
#include <iostream>
#include <string>

using namespace std;

/* *********************************************************************
Function Name: Round (Constructor)
Purpose: To initialize a new round object with default game state values.
Parameters: None.
Return Value: None.
Algorithm:
   1) Initialize round number to 1 and engine index to 0.
   2) Set default engine tiles to "6-6".
   3) Populate the list of rotating required engines from 6-6 to 0-0.
   4) Reset all player pass statuses to false.
Reference: re-modeled all functions and constructors with help of Gemini.
********************************************************************* */
Round::Round() :
    roundNum(1),
    engineIndex(0),
    currentPlayer(0),
    nextPlayer(0),
    roundOverFlag(false)
    {
    requiredEngines = { "6-6", "5-5", "4-4", "3-3", "2-2", "1-1", "0-0" };
    passed.fill(false);
    }

/* *********************************************************************
Function Name: isRoundOver
Purpose: To check if the current round has concluded.
Parameters: None.
Return Value: Boolean; true if the round is over.
Reference: None.
********************************************************************* */
bool Round::isRoundOver() const {
    return roundOverFlag;
}

/* *********************************************************************
Function Name: roundOver
Purpose: To signal that the current round has ended.
Parameters: None.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::roundOver() {
    roundOverFlag = true;
}

/* *********************************************************************
Function Name: nextRound
Purpose: To advance the game state to the next round.
Parameters: None.
Return Value: None.
Algorithm:
   1) Set roundOverFlag to false to allow new play.
   2) Increment the round count.
   3) Reset passes for all players.
Reference: None.
********************************************************************* */
void Round::nextRound() {
    roundOverFlag = false;
    roundNum++;
    resetPasses();
}

/* *********************************************************************
Function Name: setRoundNum
Purpose: To manually set the current round number.
Parameters:
   roundNumber, an integer representing the new round count.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setRoundNum(int roundNumber) {
    this->roundNum = roundNumber;
}

/* *********************************************************************
Function Name: getRoundNum
Purpose: To retrieve the current round number.
Parameters: None.
Return Value: Integer representing the round count.
Reference: None.
********************************************************************* */
int Round::getRoundNum() const {
    return roundNum;
}

/* *********************************************************************
Function Name: incEIndex
Purpose: To increment the index used to track which double is required.
Parameters: None.
Return Value: None.
Algorithm:
   1) Increment the index by one.
   2) Use modulo operation with the size of requiredEngines to wrap around.
Reference: Built by me but static_cast added by gemini
********************************************************************* */
void Round::incEIndex() {
    engineIndex = (engineIndex + 1) % static_cast<int>(requiredEngines.size());
}


/* *********************************************************************
Function Name: getEngine
Purpose: To retrieve the engine tile currently on the board.
Parameters: None.
Return Value: String representation of the engine tile.
Reference: None.
********************************************************************* */
/**string Round::getEngine() const {
    return engine;
} */

/* *********************************************************************
Function Name: getRequiredEngine
Purpose: To retrieve the tile required to start the current round.
Parameters: None.
Return Value: String representing the required double.
Reference: None.
********************************************************************* */
string Round::getRequiredEngine() const {
    return requiredEngine;
}

/* *********************************************************************
Function Name: determineEngine
Purpose: To check if a specific hand contains the required engine tile.
Parameters:
   playerHand, a vector of strings passed by reference.
Return Value: The matching tile string, or an empty string if not found.
Algorithm:
   1) Iterate through the player's tiles.
   2) Compare each tile to the requiredEngine value.
   3) Return the tile if a match is found.
Reference: Assistance from chatgpt.
********************************************************************* */
string Round::determineEngine(const vector<string>& playerHand) {
    for (const auto& tile : playerHand) {
        if (tile == requiredEngine) {
            return tile;
        }
    }
    return "";
}

/* *********************************************************************
Function Name: determineRequiredEngine
Purpose: To calculate which engine is required based on the round number.
Parameters: None.
Return Value: None.
Algorithm:
   1) Calculate the index using (roundNum - 1) % 7.
   2) Set the requiredEngine from the pre-defined list.
Reference: None.
********************************************************************* */
void Round::determineRequiredEngine() {
    int index = (roundNum - 1) % requiredEngines.size();
    requiredEngine = requiredEngines[index];
}

/* *********************************************************************
Function Name: setCurrentPlayer
Purpose: To update the index of the player whose turn it is.
Parameters:
   playerIndex, an integer (0 for Human, 1 for Computer).
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setCurrentPlayer(int playerIndex) {
    this->currentPlayer = playerIndex;
}

/* *********************************************************************
Function Name: setNextPlayer
Purpose: To update the index of the player who will move next.
Parameters:
   playerIndex, an integer.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setNextPlayer(int playerIndex) {
    this->nextPlayer = playerIndex;
}

/* *********************************************************************
Function Name: getCurrentPlayer
Purpose: To retrieve the index of the current active player.
Parameters: None.
Return Value: Integer player index.
Reference: None.
********************************************************************* */
int Round::getCurrentPlayer() const {
    return currentPlayer;
}

/* *********************************************************************
Function Name: getNextPlayer
Purpose: To retrieve the index of the player next in turn.
Parameters: None.
Return Value: Integer player index.
Reference: None.
********************************************************************* */
int Round::getNextPlayer() const {
    return nextPlayer;
}

/* *********************************************************************
Function Name: resetPasses
Purpose: To clear the pass status for all players at the start of a turn cycle.
Parameters: None.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::resetPasses() {
    passed[0] = false;
    passed[1] = false;
}

/* *********************************************************************
Function Name: setPassed
Purpose: To record that a specific player has passed their turn.
Parameters:
   playerIndex, an integer representing the player.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setPassed(int playerIndex) {
    passed[playerIndex] = true;
}

/* *********************************************************************
Function Name: resetPass
Purpose: To clear the pass status for a specific player after they move.
Parameters:
   playerIndex, an integer representing the player.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::resetPass(int playerIndex) {
    passed[playerIndex] = false;
}

/* *********************************************************************
Function Name: bothPassed
Purpose: To check if both players have passed consecutively.
Parameters: None.
Return Value: Boolean; true if both pass flags are set.
Reference: None.
********************************************************************* */
bool Round::bothPassed() const {
    return passed[0] && passed[1];
}

/* *********************************************************************
Function Name: isPassed
Purpose: To check if a specific player is currently in a passed state.
Parameters:
   playerIndex, an integer.
Return Value: Boolean pass status.
Reference: None.
********************************************************************* */
bool Round::isPassed(int playerIndex) const {
    return passed[playerIndex];
}

/* *********************************************************************
Function Name: yesNo
Purpose: Converts a boolean state to a printable "Yes" or "No" string.
Parameters:
   stateValue, a boolean value.
Return Value: A string.
Reference: Assistance from chatgpt.
********************************************************************* */
string Round::yesNo(bool stateValue) const {
    return stateValue ? "Yes" : "No";
}

/* *********************************************************************
Function Name: checkWinner
Purpose: To determine if either player has won the round by emptying their hand.
Parameters:
   humanPlayer, a Player object pointer. Passed by value.
   computerPlayer, a Player object pointer. Passed by value.
Return Value: A pointer to the winning Player, or nullptr if none.
Algorithm:
   1) Access the human player's hand tiles; if empty, human wins.
   2) Access the computer player's hand tiles; if empty, computer wins.
   3) Otherwise, return nullptr.
Reference: Assistance from chatgpt.
********************************************************************* */
Player* Round::checkWinner(Player* humanPlayer, Player* computerPlayer) {
    // Access hand tiles via the hand object
    if (humanPlayer->getHand().getHandTiles().empty()) {
        cout << "Human wins the round" << endl;
        return humanPlayer;
    }
    if (computerPlayer->getHand().getHandTiles().empty()) {
        cout << "Computer wins the round" << endl;
        return computerPlayer;
    }
    return nullptr;
}