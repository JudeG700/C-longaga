#pragma once

#include <iostream>
#include <vector>
#include <array>
#include <string>

#include "player.h"

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>

/**
 * @class Round
 * @brief Manager class for individual round state and rules.
 * * This class tracks the flow of a single round, including turn management,
 * the 'Engine' rotation (6-6, 5-5, etc.), and passing logic. It is
 * fully serializable via the Cereal library to allow for game resumption.
 */

class Round
{
private:
    int roundNum = 1;                     ///< Current round number in the tournament.
    bool hasPassed = false;               ///< General flag for a pass event.
    std::array<bool, 2> passed{ false, false }; ///< Tracks individual pass status for both players.
    int engineIndex = 0;                  ///< Index for the currently required engine tile.
    int currentPlayer = 0;                ///< Index of the player whose turn it is (0: Human, 1: Computer).
    int nextPlayer = 0;                   ///< Index of the player up next.
    bool roundOverFlag = false;           ///< Flag indicating the current round has concluded.

    std::string engine = "6-6"; ///< the current engine
    std::string requiredEngine = "6-6"; ///< the current required engine
    std::vector<std::string> requiredEngines{ ///< The list of required engines
        "6-6", "5-5", "4-4", "3-3", "2-2", "1-1", "0-0"
    };

public:
    Round();

    /**
    * @brief Serializes the complete state of the round.
    * Ensures all turn and engine data is preserved in the JSON save file.
    */    
   
    // round state
    bool isRoundOver() const;
    void roundOver();
    void nextRound();
    int getRoundNum() const;

    //for serialization
    void setRoundNum(int roundNum);

    // engine logic
    void updateRequiredEngine();
    void incEIndex();
    void setEngine(const std::string& engine);
    void setRequiredEngine();
    std::string getEngine() const;
    std::string getRequiredEngine() const;
    void determineRequiredEngine();

    /**
     * @brief Checks if the provided hand contains the engine required for the current round.
     * @param hand The vector of tiles to search.
     * @return The engine tile string if found, otherwise an empty string.
     */
    std::string determineEngine(const std::vector<std::string>& hand);

    // player turn tracking
    void setCurrentPlayer(int currentPlayer);
    void setNextPlayer(int nextPlayer);

    int getCurrentPlayer() const;
    int getNextPlayer() const;

    // passing
    void resetPasses();
    void setPassed(int playerIndex);
    void resetPass(int playerIndex);
    void clearPassed(int playerIndex);

    //passing logic
    /** @brief Returns true if both players have passed consecutively (tied game). */
    bool bothPassed() const;
    bool isPassed(bool player) const;

    // helpers
    std::string yesNo(bool value) const;

    /**
    * @brief Evaluates hands to see if a player has emptied their hand.
    * @return Pointer to the winning Player object, or nullptr if the round continues.
    */    
    Player* checkWinner(Player* human, Player* computer);
};
