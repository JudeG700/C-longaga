#pragma once

#include <iostream>
#include <string>
#include "player.h"

/* *********************************************************************
Class Name: Tournament
Purpose: Oversees the high-level scoring and victory conditions for the
         game session. Maintains cumulative scores across rounds and
         defines the target threshold for the final champion.
********************************************************************* */
class Tournament {

public:

    // --- 1. Constants ---
// Symbolic constant to avoid magic numbers in the code

    // --- 2. Constructors ---
    /* *********************************************************************
    Function Name: Tournament (Default)
    Purpose: To initialize a tournament with starting scores and defaults.
    Parameters: none
    Algorithm:
                1) Use member initialization to set scores to 0.
                2) Set target score to the default winning threshold.
    ********************************************************************* */
    Tournament() : humanScore(0), computerScore(0), targetScore(0) {};

    // --- 3. Destructor ---
    virtual ~Tournament() {}

    // --- 4. Selectors ---

    /* *********************************************************************
    Function Name: getPlayerScore
    Purpose: Returns the Human player's current cumulative score.
    Return Value: int, total points.
    ********************************************************************* */
    int getPlayerScore() const;

    /* *********************************************************************
    Function Name: getComputerScore
    Purpose: Returns the Computer player's current cumulative score.
    Return Value: int, total points.
    ********************************************************************* */
    int getComputerScore() const;

    /* *********************************************************************
    Function Name: getTournScore
    Purpose: Returns the target score needed to win the tournament.
    Return Value: int, target threshold.
    ********************************************************************* */
    int getTournScore() const;

    // --- 5. Mutators ---

    /* *********************************************************************
    Function Name: addPlayerScore
    Purpose: Adds round points to the Human's tournament total.
    Parameters: points, integer value.
    ********************************************************************* */
    void addPlayerScore(int points);

    /* *********************************************************************
    Function Name: addComputerScore
    Purpose: Adds round points to the Computer's tournament total.
    Parameters: points, integer value.
    ********************************************************************* */
    void addComputerScore(int points);

    /* *********************************************************************
    Function Name: setTournScore
    Purpose: Updates the score threshold required to win the tournament.
    Parameters: winningThreshold, integer.
    ********************************************************************* */
    void setTournScore(int winningThreshold);

    /* *********************************************************************
    Function Name: setHumanScore
    Purpose: Explicitly sets the human's tournament score (for loading).
    Parameters: newScore, integer.
    ********************************************************************* */
    void setHumanScore(int newScore);

    /* *********************************************************************
    Function Name: setComputerScore
    Purpose: Explicitly sets the computer's tournament score (for loading).
    Parameters: newScore, integer.
    ********************************************************************* */
    void setComputerScore(int newScore);

    // --- 6. Utility Functions ---

    /* *********************************************************************
    Function Name: determineWinner
    Purpose: Evaluates scores against the target to identify a champion.
    Return Value: std::string, "Human", "Computer", or empty string.
    Algorithm:
                1) Compare scores to targetScore.
                2) Return winner's ID or empty if no winner yet.
    ********************************************************************* */
    std::string determineWinner();

protected:
    // (None)

private:

    // Cumulative scores
    int humanScore;
    int computerScore;

    // The score threshold required to win
    int targetScore;

}; 