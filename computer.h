#pragma once

#include "player.h"
#include "hand.h"
#include "stock.h"
#include <vector>
#include <string>
#include <set>

// Forward declaration to avoid circular dependency with Round
class Round;

/* *********************************************************************
Class Name: Computer
Purpose: Represents the AI opponent. Implements automated decision-making
         logic based on a weighted scoring heuristic.
Inheritance: Publicly inherits from the Player class.
********************************************************************* */
class Computer : public Player {


public:

    
    // --- 1. Constants ---
    // (None currently defined for this class)

    // --- 2. Constructors ---

    /* *********************************************************************
    Function Name: Computer (Default)
    Purpose: Initializes a computer player with an empty hand.
    Parameters: none
    Algorithm:
                1) Use member initialization list to set the hand.
    ********************************************************************* */
    Computer() : Player() {}

    /* *********************************************************************
    Function Name: Computer (Parameterized)
    Purpose: Initializes the computer player with a specific hand.
    Parameters:
                hand: A Hand object passed by value.
    Algorithm:
                1) Initialize the base Player class with the provided hand.
    ********************************************************************* */
    Computer(Hand hand) : Player(hand) {}

    // --- 3. Destructor ---
    virtual ~Computer() {}

    // --- 4. Selectors ---

    /* *********************************************************************
    Function Name: returnID
    Purpose: Identifies the player type.
    Parameters: none
    Return Value: std::string, always returns "Computer".
    ********************************************************************* */
    std::string returnID() const override;

    /* *********************************************************************
    Function Name: isDouble
    Purpose: Determines if a tile is a double (both sides equal).
    Parameters:
                a: int, left pip value.
                b: int, right pip value.
    Return Value: bool, true if pips match.
    ********************************************************************* */
    bool isDouble(int a, int b) const;

    /* *********************************************************************
    Function Name: tileWeight
    Purpose: Calculates the sum of pips for a tile.
    Parameters:
                a: int, left pip value.
                b: int, right pip value.
    Return Value: int, the sum of the pips.
    ********************************************************************* */
    int tileWeight(int a, int b) const;

    // --- 5. Mutators ---
    // (Note: Computer moves are calculated internally, not set by client)

    // --- 6. Utility Functions ---

    /* *********************************************************************
    Function Name: takeTurn
    Purpose: Primary AI controller to decide the best move.
    Parameters:
                gameStock: Stock object.
                gameRound: Round object.
                leftEnd: int, layout's current left end.
                rightEnd: int, layout's current right end.
    Return Value: Move structure containing the AI's choice.
    ********************************************************************* */
    Move takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd) override;

    /* *********************************************************************
    Function Name: findPlayableTiles
    Purpose: Scans the hand for tiles that can be legally played.
    Parameters:
                hand: Hand object.
                gameRound: Round reference.
                leftEnd: int, current left end.
                rightEnd: int, current right end.
    Return Value: std::vector<int>, indices of playable tiles.
    ********************************************************************* */
    //std::vector<int> findPlayableTiles(Hand hand, Round& gameRound, int leftEnd, int rightEnd) override;
    std::vector<Player::PlayableOption> findPlayableTiles(Hand hand, Round& gameRound, int leftEnd, int rightEnd);

    /* *********************************************************************
    Function Name: scoreTile
    Purpose: Heuristic to evaluate a tile's strategic value.
    Parameters:
                a, b: pips.
                leftEnd, rightEnd: layout ends.
                blockedNumbers: set of integers currently blocked.
    Return Value: int, the heuristic score.
    ********************************************************************* */
    int scoreTile(int a, int b, int leftEnd, int rightEnd, char scoreTile, std::string player);

    /* *********************************************************************
    Function Name: help
    Purpose: Provides the human player with the AI's suggested move.
    Parameters:
                player: Pointer to the Human player.
                gamestock: Stock object.
                gameRound: Round object.
                leftEnd, rightEnd: layout ends.
    Return Value: none (outputs recommendation to console).
    ********************************************************************* */
    void help(Player* player, Stock gamestock, Round gameRound, int leftEnd, int rightEnd);

protected:
    // (None currently defined for this class)

private:
    // --- 7. Variables ---
    std::string ID = "Computer";

    // --- 8. Private Utility Functions ---

    /* *********************************************************************
    Function Name: parseTile
    Purpose: Converts string tile ("6-6") to numeric values.
    Parameters:
                tile: std::string representation.
    Return Value: std::pair<int, int>, the two numeric pips.
    ********************************************************************* */
    std::pair<int, int> parseTile(const std::string& tile);

};