#include "tournament.h"

/* *********************************************************************
Function Name: addPlayerScore
Purpose: To update the human player's cumulative tournament total.
Parameters:
            points, an integer. The sum of pips from the opponent's hand.
            Passed by value.
Return Value: None.
Algorithm:
            1) Receive the calculated point value from the completed round.
            2) Add this value to the human player's total tournament score.
Reference: None.
********************************************************************* */
void Tournament::addPlayerScore(int points)
{
    humanScore += points;
}

/* *********************************************************************
Function Name: addComputerScore
Purpose: To update the computer player's cumulative tournament total.
Parameters:
            points, an integer. The sum of pips from the opponent's hand.
            Passed by value.
Return Value: None.
Algorithm:
            1) Receive the calculated point value from the completed round.
            2) Add this value to the computer player's total tournament score.
Reference: None.
********************************************************************* */
void Tournament::addComputerScore(int points)
{
    computerScore += points;
}

/* *********************************************************************
Function Name: getPlayerScore
Purpose: To retrieve the human player's current total points.
Parameters: None.
Return Value: Integer, the current score.
Reference: None.
********************************************************************* */
int Tournament::getPlayerScore() const
{
    return humanScore;
}

/* *********************************************************************
Function Name: getComputerScore
Purpose: To retrieve the computer player's current total points.
Parameters: None.
Return Value: Integer, the current score.
Reference: None.
********************************************************************* */
int Tournament::getComputerScore() const
{
    return computerScore;
}

/* *********************************************************************
Function Name: getTournScore
Purpose: To retrieve the target score required to win the tournament.
Parameters: None.
Return Value: Integer, the winning threshold.
Reference: None.
********************************************************************* */
int Tournament::getTournScore() const
{
    return targetScore;
}

void Tournament::setTournScore(int targetScore)
{
    this->targetScore = targetScore;
}
/* *********************************************************************
Function Name: determineWinner
Purpose: To evaluate if the tournament has concluded and identify the victor.
Parameters: None.
Return Value: A string containing the name of the winner ("Human" or "Computer"),
              or an empty string if the tournament is still in progress.
Algorithm:
            1) Check if either player has reached or exceeded the target score.
            2) If the threshold is met, compare the human and computer scores.
            3) Identify the player with the higher total as the winner.
            4) Return the result or signal that the tournament continues.
Reference: chatgpt helped with building this
********************************************************************* */
std::string Tournament::determineWinner()
{
    if (humanScore >= targetScore || computerScore >= targetScore)
    {
        return (humanScore > computerScore) ? "Human" : "Computer";
    }
    return ""; // Tournament continues
}
