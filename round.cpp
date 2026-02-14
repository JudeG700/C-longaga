#include "round.h"

using namespace std;

/* *********************************************************************
Function Name: Round (Constructor)
Purpose: To initialize the Round object with default state values.
Parameters: none
Return Value: none
Reference: none
********************************************************************* */
Round::Round() = default;

/* *********************************************************************
Function Name: isRoundOver
Purpose: To check if the current round has concluded.
Parameters: none
Return Value: boolean, true if round is over, false otherwise.
Reference: none
********************************************************************* */
bool Round::isRoundOver() const
{
    return roundOverFlag;
}

/* *********************************************************************
Function Name: roundOver
Purpose: To manually signal the end of a round.
Parameters: none
Return Value: none
Reference: none
********************************************************************* */
void Round::roundOver()
{
    roundOverFlag = true;
}

/* *********************************************************************
Function Name: nextRound
Purpose: To reset the game state for a new round.
Parameters: none
Return Value: none
Algorithm:
            1) Reset the roundOverFlag to false.
            2) Increment the round counter.
            3) Reset the pass flags for both players.
Reference: none
********************************************************************* */
void Round::nextRound()
{
    roundOverFlag = false;
    roundNum++;
    resetPasses();
}

void Round::setRoundNum(int roundNum)
{
    this->roundNum = roundNum;
}

/* *********************************************************************
Function Name: getRoundNum
Purpose: To retrieve the current round number.
Parameters: none
Return Value: integer, the current round.
Reference: none
********************************************************************* */
int Round::getRoundNum() const
{
    return roundNum;
}

/* *********************************************************************
Function Name: updateRequiredEngine
Purpose: To update the engine tile required for the current round.
Parameters: none
Return Value: none
Algorithm:
            1) Check if the engine index is within bounds of the engines vector.
            2) Set the required engine to the engine at that index.
Reference: none
********************************************************************* */
void Round::updateRequiredEngine()
{
    if (engineIndex < requiredEngines.size())
    {
        requiredEngine = requiredEngines[engineIndex];
    }
}
/* *********************************************************************
Function Name: incEIndex
Purpose: To cycle to the next required engine in the sequence.
Parameters: none
Return Value: none
Algorithm:
            1) Increment the engine index so the next engine is picked (if a round passes).
            2) Use modulo to wrap back to the start if the end is reached.
Reference: none
********************************************************************* */
void Round::incEIndex()
{
    engineIndex = (engineIndex + 1) % requiredEngines.size();
}

/* *********************************************************************
Function Name: setEngine
Purpose: To set the engine tile played for the round.
Parameters:
            engine, a string representing the tile.
Return Value: none
Reference: none
********************************************************************* */
void Round::setEngine(const string& engine)
{
    this->engine = engine;
}

/* *********************************************************************
Function Name: setRequiredEngine
Purpose: To set the required engine based on the current index.
Parameters: none
Return Value: none
Reference: none
********************************************************************* */
void Round::setRequiredEngine()
{
    requiredEngine = requiredEngines[engineIndex];
}

/* *********************************************************************
Function Name: getEngine
Purpose: To retrieve the engine tile played.
Parameters: none
Return Value: string, the engine tile.
Reference: none
********************************************************************* */
string Round::getEngine() const
{
    return engine;
}

/* *********************************************************************
Function Name: getRequiredEngine
Purpose: To retrieve the engine required to start the round.
Parameters: none
Return Value: string, the required engine tile.
Reference: none
********************************************************************* */
string Round::getRequiredEngine() const
{
    return requiredEngine;
}

/* *********************************************************************
Function Name: determineEngine
Purpose: To check if a specific hand contains the required engine.
Parameters:
            hand, a vector of strings representing the player's tiles.
Return Value: string, the engine tile if found, otherwise an empty string.
Algorithm:
            1) Iterate through the player's hand.
            2) If a tile matches the required engine, return that tile.
            3) Return empty string if no match is found.
Reference: chatgpt built
********************************************************************* */
string Round::determineEngine(const vector<string>& hand)
{
    for (const auto& tile : hand)
    {
        if (tile == requiredEngine)
        {
            return tile;
        }
    }
    return "";
}

void Round::determineRequiredEngine()
{   
    int index = roundNum - 1;
    index = index % 7;
    requiredEngine = requiredEngines[roundNum - 1];

}
// ---------------- Players ----------------
/* *********************************************************************
Function Name: setCurrentPlayer
Purpose: To set which player is currently taking a turn.
Parameters:
            currentPlayer, an integer (0 or 1).
Return Value: none
Reference: none
********************************************************************* */
void Round::setCurrentPlayer(int currentPlayer)
{
    this->currentPlayer = currentPlayer;
}

/* *********************************************************************
Function Name: setNextPlayer
Purpose: To set the index of the next player.
Parameters:
            nextPlayer, an integer.
Return Value: none
Reference: none
********************************************************************* */
void Round::setNextPlayer(int nextPlayer)
{
    this->nextPlayer = nextPlayer;
}

/* *********************************************************************
Function Name: getCurrentPlayer
Purpose: To get the index of the current player.
Parameters: none
Return Value: integer, the current player index.
Reference: none
********************************************************************* */
int Round::getCurrentPlayer() const
{
    return currentPlayer;
}

/* *********************************************************************
Function Name: getNextPlayer
Purpose: To get the index of the next player.
Parameters: none
Return Value: integer, the next player index.
Reference: none
********************************************************************* */
int Round::getNextPlayer() const
{
    return nextPlayer;
}

// ---------------- Passing ----------------

/* *********************************************************************
Function Name: resetPasses
Purpose: To reset the pass status for both players.
Parameters: none
Return Value: none
Algorithm:
            1) Set both indices of the passed array to false.
Reference: none
********************************************************************* */
void Round::resetPasses()
{
    passed[0] = false;
    passed[1] = false;
}

/* *********************************************************************
Function Name: setPassed
Purpose: To record that a player has passed their turn.
Parameters:
            playerIndex, an integer.
Return Value: none
Reference: none
********************************************************************* */
void Round::setPassed(int playerIndex)
{
    passed[playerIndex] = true;
}

/* *********************************************************************
Function Name: resetPass
Purpose: To clear a single player's pass status.
Parameters:
            playerIndex, an integer.
Return Value: none
Reference: none
********************************************************************* */
void Round::resetPass(int playerIndex)
{
    passed[playerIndex] = false;
}

/* *********************************************************************
Function Name: clearPassed
Purpose: Alias for resetPass.
Parameters:
            playerIndex, an integer.
Return Value: none
Reference: none
********************************************************************* */
void Round::clearPassed(int playerIndex)
{
    passed[playerIndex] = false;
}

/* *********************************************************************
Function Name: bothPassed
Purpose: To detect if both players have passed consecutively (blocked game).
Parameters: none
Return Value: boolean, true if both passed.
Algorithm:
            1) Return the logical AND of when both players passed.
Reference: chatgpt
********************************************************************* */
bool Round::bothPassed() const
{
    return passed[0] && passed[1];
}

/* *********************************************************************
Function Name: isPassed
Purpose: To check if a specific player passed their last turn.
Parameters:
            player, an integer/boolean index.
Return Value: boolean status.
Algorithm:
            1) Return the passed status for the given index.
Reference: none
********************************************************************* */
bool Round::isPassed(bool player) const
{
    return passed[player];
}


/* *********************************************************************
Function Name: yesNo
Purpose: Utility to convert a boolean to a string for display.
Parameters:
            value, a boolean.
Return Value: string, "Yes" or "No".
Algorithm:
            1) Return "Yes" if true, "No" if false.
Reference: chatgpt helped build this function
********************************************************************* */
string Round::yesNo(bool value) const
{
    return value ? "Yes" : "No";
}

/* *********************************************************************
Function Name: checkWinner
Purpose: To identify if a player has run out of tiles and won the round.
Parameters:
            human, pointer to Human player.
            computer, pointer to Computer player.
Return Value: Player pointer to the winner, or nullptr if no winner yet.
Algorithm:
            1) Check if human hand is empty. If so, return human.
            2) Check if computer hand is empty. If so, return computer.
            3) Return nullptr if neither hand is empty.
Reference: Logic for winner detection assisted by chatgpt
********************************************************************* */
Player* Round::checkWinner(Player* human, Player* computer)
{
    if (human->getHand().getHandTiles().empty())
    {
        cout << "Player wins the round\n";
        return human;
    }
    if (computer->getHand().getHandTiles().empty())
    {
        cout << "Computer wins the round\n";
        return computer;
    }
    return nullptr;
}
