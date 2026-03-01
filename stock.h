#pragma once

#include <vector>
#include <string>

/* *********************************************************************
Class Name: Stock
Purpose: Manages the collection of all dominoes not currently in a player's
         hand (the boneyard). Handles initialization of the 28-tile set,
         shuffling logic, and tile distribution.
********************************************************************* */
class Stock {

public:
    // --- 1. Constants ---
    // Rule: Use symbolic constants, no magic numbers.
    static const short INITIAL_DEAL_COUNT = 8;
    static const short MAX_PIP_VALUE = 6;

    // --- 2. Constructors ---
    /* *********************************************************************
    Function Name: Stock (Default)
    Purpose: To initialize the boneyard with a full set of dominoes.
    Parameters: none
    Algorithm:
                1) Create a standard double-six set (28 tiles).
                2) Store them in the boneyard vector.
    ********************************************************************* */
    Stock();

    // --- 3. Destructor ---
    virtual ~Stock() {}

    // --- 4. Selectors ---
    /* *********************************************************************
    Function Name: display
    Purpose: Prints all remaining tiles in the boneyard.
    Parameters: none
    Return Value: none (outputs to console)
    ********************************************************************* */
    void display() const;

    /* *********************************************************************
    Function Name: getBoneyard
    Purpose: Returns a copy of the current boneyard.
    Parameters: none
    Return Value: std::vector<std::string>, a copy of internal storage.
    ********************************************************************* */
    std::vector<std::string> getBoneyard() const;

    // --- 5. Mutators ---
    /* *********************************************************************
    Function Name: setBoneyard
    Purpose: Explicitly sets the tiles in the boneyard (for loading games).
    Parameters:
                tiles: std::vector of strings.
    Algorithm:
                1) Assign the passed vector to the internal boneyard.
    ********************************************************************* */
    void setBoneyard(std::vector<std::string> tiles);

    /* *********************************************************************
    Function Name: shuffle
    Purpose: Randomizes the order of tiles using a Fisher-Yates shuffle.
    Parameters: none
    Algorithm:
                1) Iterate through the vector from back to front.
                2) Swap each element with a randomly selected previous element.
    ********************************************************************* */
    void shuffle();

    /* *********************************************************************
    Function Name: drawTile
    Purpose: Removes and returns the top tile from the boneyard.
    Parameters: none
    Return Value: std::string, the tile value or empty string if empty.
    ********************************************************************* */
    std::string drawTile();

    /* *********************************************************************
    Function Name: deal
    Purpose: Deals a starting hand of tiles to a player.
    Parameters: none
    Return Value: std::vector<std::string>, a collection of 8 tiles.
    ********************************************************************* */
    std::vector<std::string> deal();

    /* *********************************************************************
    Function Name: reset
    Purpose: Resets the boneyard to a full, shuffled 28-tile set.
    Parameters: none
    Algorithm:
                1) Clear the current boneyard.
                2) Re-populate with 28 tiles and shuffle.
    ********************************************************************* */
    void reset();

    void empty();

protected:
    // (None)

private:
    // --- 6. Variables ---
    // Mnemonic names and private for encapsulation
    std::vector<std::string> boneyard;

}; // <--- The most important semicolon in the world.