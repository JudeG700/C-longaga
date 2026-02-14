#pragma once

#include <iostream>
#include <string>

#include "player.h"

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>


/**
 * @class Tournament
 * @brief Oversees the high-level scoring and victory conditions for the game session.
 * * This class maintains the cumulative scores for both the Human and Computer players
 * across multiple rounds. It defines the 'target score' required to win the
 * overall tournament and provides the logic to determine the final champion.
 */
class Tournament
{
private:
    Player* p1;             ///< Pointer to the Human player object.
    Player* p2;             ///< Pointer to the Computer player object.
    int humanScore = 0;     ///< Cumulative tournament points for the Human.
    int computerScore = 0;   ///< Cumulative tournament points for the Computer.
    int targetScore = 200;  ///< The score threshold required to win the tournament.

public:

    /**
     * @brief Serializes the tournament's progress.
     * Only the cumulative scores are archived to JSON, as the player objects
     * are reconstructed during the loading process.
     */

    /** @brief Adds points earned in a round to the Human's tournament total. */
    void addPlayerScore(int points);

    /** @brief Adds points earned in a round to the Computer's tournament total. */
    void addComputerScore(int points);

    /** @return The Human player's current cumulative score. */
    int getPlayerScore() const;

    /** @return The Computer player's current cumulative score. */
    int getComputerScore() const;

    
    /** @return The fixed target score (e.g., 200) needed to end the tournament. */
    int getTournScore() const;

    void setTournScore(int targetScore);

    void setHumanScore(int humanScore)
    {
        this->humanScore = humanScore;

    }
    void setComputerScore(int humanScore)
    {
        this->computerScore = computerScore;

    }
    /** * @brief Checks if either player has reached the target score.
     * @return A string ("Human" or "Computer") identifying the winner, or an empty string if ongoing.
     */
    std::string determineWinner();
};
