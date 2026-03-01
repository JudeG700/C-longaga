#pragma once

#include "hand.h"
#include <vector>
//#include "move.h"
#include "stock.h"
#include <iostream>
#include <set>
#include <string>

// Forward declaration to handle the circular dependency with Round
class Round;


/* *********************************************************************
Class Name: Player
Purpose: Abstract Base Class providing the core interface for all game
         participants. Enforces a consistent gameplay interface for
         Human and AI players through polymorphism.
********************************************************************* */
class Player {

public:

    struct PlayableOption {
        int index;
        char side; // 'L' for Left, 'R' for Right
    };

    struct Move {
        std::string chosenTile;
        char side;   // 'L' or 'R'
        bool draw;   // true if drawing from boneyard
        bool passed;
        bool help;
        bool hasPlayableTiles;
    };

    // --- 1. Constants ---
    // (None defined at the base level)

    // --- 2. Constructors ---

    /* *********************************************************************
    Function Name: Player (Default)
    Purpose: Initializes a player with a default state and zero score.
    Parameters: none
    Algorithm:
                1) Use member initializer syntax to set score to 0.
                2) Set default identifier to "Player".
    ********************************************************************* */
    Player() : score(0), ID("Player") {}

    /* *********************************************************************
    Function Name: Player (Parameterized)
    Purpose: Robustly initializes a player using an existing Hand object.
    Parameters:
                initialHand: A Hand object passed by value.
    Algorithm:
                1) Initialize score to 0.
                2) Assign the tiles from initialHand to the internal hand member.
    ********************************************************************* */
    Player(Hand initialHand) : score(0), ID("Player") {
        this->hand = initialHand;
    }

    // --- 3. Destructor ---
    /* *********************************************************************
    Function Name: ~Player
    Purpose: Virtual destructor to ensure proper cleanup of derived objects.
    ********************************************************************* */
    virtual ~Player() {}

    // --- 4. Selectors ---

    /* *********************************************************************
    Function Name: getHand
    Purpose: Returns a copy of the player's Hand object.
    Parameters: none
    Return Value: Hand, a copy of the internal hand member (Reliability rule).
    ********************************************************************* */
    Hand getHand() const;

    /* *********************************************************************
    Function Name: getHandTiles
    Purpose: Returns the vector of tile strings.
    Parameters: none
    Return Value: std::vector<std::string>, a copy of the tile collection.
    ********************************************************************* */
    std::vector<std::string> getHandTiles() const;

    /* *********************************************************************
    Function Name: getScore
    Purpose: Returns the current tournament score.
    Parameters: none
    Return Value: int, the current score.
    ********************************************************************* */
    int getScore() const;

    /* *********************************************************************
    Function Name: returnID
    Purpose: Returns the identifier string.
    Parameters: none
    Return Value: std::string, the ID ("Human" or "Computer").
    ********************************************************************* */
    virtual std::string returnID() const;

    std::string getTileByIndex(int index) const;

    int getIndexByTile(std::string tile) const;
    
    // --- 5. Mutators ---

    /* *********************************************************************
    Function Name: setTiles
    Purpose: Overwrites the hand with a new collection of tiles.
    Parameters:
                deal: std::vector of strings.
    Algorithm:
                1) Take the passed vector and update internal hand tiles.
    ********************************************************************* */
    void setTiles(std::vector<std::string> deal);

    /* *********************************************************************
    Function Name: addPoints
    Purpose: Increments the player's cumulative tournament score.
    Parameters:
                points: int, number of pips to add.
    Algorithm:
                1) If points are positive, add to total score.
    ********************************************************************* */
    void addPoints(int points);

    /* *********************************************************************
    Function Name: addTile
    Purpose: Adds a single tile to the player's hand.
    Parameters:
                tile: std::string representation of a domino.
    Algorithm:
                1) Pass the tile string to the internal Hand object's add method.
    ********************************************************************* */
    void addTile(std::string tile);

    /* *********************************************************************
    Function Name: removeTile
    Purpose: Deletes a tile at a specific index from the hand.
    Parameters:
                index: int, the position of the tile to remove.
    Algorithm:
                1) Call the internal Hand object's remove method with the index.
    ********************************************************************* */
    void removeTile(int index);

    /* *********************************************************************
    Function Name: emptyHand
    Purpose: Clears all tiles from the internal Hand container.
    Parameters: none
    Algorithm:
                1) Instruct the internal Hand object to clear its collection.
    ********************************************************************* */
    void emptyHand();


    // --- 6. Utility Functions ---

    /* *********************************************************************
    Function Name: takeTurn
    Purpose: Pure virtual entry point for player decision logic.
    ********************************************************************* */
    virtual Move takeTurn(Stock &gameStock, Round gameRound, int leftEnd, int rightEnd) = 0;

    /* *********************************************************************
    Function Name: findPlayableTiles
    Purpose: Pure virtual logic to scan for legal moves.
    ********************************************************************* */
    virtual std::vector<PlayableOption> findPlayableTiles(Hand hand, Round& gameRound, int leftEnd, int rightEnd) = 0;

protected:
    // Base class members accessible by Human and Computer
    Hand hand;
    int score;
    std::string ID;

private:
    // (Private members go here if they are not meant for derived classes)

};