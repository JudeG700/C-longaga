#pragma once

#include <iostream>
#include <deque>
#include <string>

/* *********************************************************************
Class Name: Layout
Purpose: Manages the sequence of tiles played on the table (the chain).
         Provides functionality to add tiles to either end and retrieve
         the current playable pip values.
********************************************************************* */
class Layout {

public:
    // --- 1. Constants ---
    // (None defined for this class)

    // --- 2. Constructors ---

    /* *********************************************************************
    Function Name: Layout (Default)
    Purpose: Initializes an empty layout for the game board.
    Parameters: none
    Algorithm:
                1) Initialize an empty deque of strings.
    ********************************************************************* */
    Layout() {}

    // --- 3. Destructor ---
    ~Layout() {}

    // --- 4. Selectors ---

    /* *********************************************************************
    Function Name: isEmpty
    Purpose: Checks if the board currently has any tiles.
    Parameters: none
    Return Value: bool, true if the chain is empty, false otherwise.
    ********************************************************************* */
    bool isEmpty() const;

    /* *********************************************************************
    Function Name: returnLeft
    Purpose: Returns the pip value available on the left-most tile.
    Parameters: none
    Return Value: int, pip value of the left end, or -1 if empty.
    ********************************************************************* */
    int returnLeft() const;

    /* *********************************************************************
    Function Name: returnRight
    Purpose: Returns the pip value available on the right-most tile.
    Parameters: none
    Return Value: int, pip value of the right end, or -1 if empty.
    ********************************************************************* */
    int returnRight() const;

    /* *********************************************************************
    Function Name: getChain
    Purpose: Returns a copy of the current domino sequence.
    Parameters: none
    Return Value: std::deque<std::string>, a copy of the internal chain
                  (Encapsulation rule: return a copy, not a reference).
    ********************************************************************* */
    std::deque<std::string> getChain() const;

    // --- 5. Mutators ---

    /* *********************************************************************
    Function Name: addRight
    Purpose: Appends a tile to the right-hand side of the layout.
    Parameters:
                tileString: std::string representation of the domino.
    Algorithm:
                1) Push the tile string to the back of the deque.
    ********************************************************************* */
    void addRight(std::string tileString);

    /* *********************************************************************
    Function Name: addLeft
    Purpose: Appends a tile to the left-hand side of the layout.
    Parameters:
                tileString: std::string representation of the domino.
    Algorithm:
                1) Push the tile string to the front of the deque.
    ********************************************************************* */
    void addLeft(std::string tileString);

    /* *********************************************************************
    Function Name: clearChain
    Purpose: Clears all tiles from the board for a new round.
    Parameters: none
    Algorithm:
                1) Remove all elements from the internal deque.
    ********************************************************************* */
    void clearChain();

protected:
    // (No protected members)

private:
    // --- 6. Variables ---

    // Mnemonic name for the container holding the game's tile sequence
    std::deque<std::string> dominoChain;

};