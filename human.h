#pragma once

#include "hand.h"
#include "player.h"
#include <iostream>
#include "stock.h"
#include <string>
#include <vector>

// Forward declaration to resolve circular dependency
class Round;


/* *********************************************************************
Class Name: Human
Purpose: Represents the human participant in the game. Handles user
         interaction by capturing and validating console input for
         gameplay decisions.
Inheritance: Publicly inherits from the Player base class.
********************************************************************* */
class Human : public Player {

public:

    


    // --- 1. Constants ---
    // (None defined for this class)

    // --- 2. Constructors ---

    /* *********************************************************************
    Function Name: Human (Default)
    Purpose: To initialize a human player with default values.
    Parameters: none
    Algorithm:
                1) Initialize base Player class using default constructor.
    ********************************************************************* */
    Human() : Player() {}

    /* *********************************************************************
    Function Name: Human (Parameterized)
    Purpose: To initialize a human player with a starting hand.
    Parameters:
                humanHand: A Hand object passed by value (Reliability rule).
    Algorithm:
                1) Call the base Player parameterized constructor with humanHand.
    ********************************************************************* */
    Human(Hand humanHand) : Player(humanHand) {}

    // --- 3. Destructor ---
    virtual ~Human() {}

    // --- 4. Selectors ---

    /* *********************************************************************
    Function Name: returnID
    Purpose: Returns the identifier for display and logic.
    Parameters: none
    Return Value: std::string, always returns "Human".
    ********************************************************************* */
    std::string returnID() const override;

    // --- 5. Mutators ---
    // (Inherits mutators from Player)

    // --- 6. Utility Functions ---

    /* *********************************************************************
    Function Name: takeTurn
    Purpose: Facilitates the human's turn via console input and validation.
    Parameters:
                gameStock: Stock object (passed by value).
                gameRound: Round object.
                leftEnd: int, layout's current left end.
                rightEnd: int, layout's current right end.
    Return Value: Move structure containing the validated decision.
    ********************************************************************* */
    Player::Move takeTurn(Stock &gameStock, Round gameRound, int leftEnd, int rightEnd) override;

    /* *********************************************************************
    Function Name: findPlayableTiles
    Purpose: Identifies which tiles in the hand can be legally played.
    Parameters:
                hand: Hand object.
                gameRound: Round reference.
                leftEnd: int, current left end.
                rightEnd: int, current right end.
    Return Value: std::vector<int>, indices of playable tiles.
    ********************************************************************* */
    std::vector<Player::PlayableOption> findPlayableTiles(Hand hand, Round& gameRound, int leftEnd, int rightEnd);

    /* *********************************************************************
    Function Name: parseTile
    Purpose: Converts string tile representation to numeric pip values.
    Parameters:
                tileString: std::string (e.g., "5-4").
    Return Value: std::pair<int, int>, the pips as integers.
    ********************************************************************* */
    std::pair<int, int> parseTile(const std::string& tileString);

protected:
    // (Inherits protected members from Player)

private:
    // --- 7. Variables ---
    std::string ID = "Human";

};