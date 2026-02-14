

#include <iostream>
#include <deque>
#include "layout.h"
using namespace std;


/* *********************************************************************
Function Name: returnLeft
Purpose: To identify the current playable value at the left end of the layout.
Parameters: None.
Return Value: Integer, representing the outward-facing pips on the left.
Algorithm:
            1) Access the domino tile at the front of the chain.
            2) Extract the character representing the left-most value.
            3) Convert the character to its numeric integer equivalent and return it.
Reference: None.
********************************************************************* */
int Layout::returnLeft()
{
    return dominoChain.front()[0] - '0';
}

/* *********************************************************************
Function Name: returnRight
Purpose: To identify the current playable value at the right end of the layout.
Parameters: None.
Return Value: Integer, representing the outward-facing pips on the right.
Algorithm:
            1) Access the domino tile at the back of the chain.
            2) Extract the character representing the right-most value.
            3) Convert the character to its numeric integer equivalent and return it.
Reference: None.
********************************************************************* */
int Layout::returnRight()
{
    return dominoChain.back()[2] - '0';
}

/* *********************************************************************
Function Name: addRight
Purpose: To extend the game board by adding a validated tile to the right side.
Parameters:
            tile, a string representing the domino. Passed by value.
Return Value: None.
Algorithm:
            1) Append the new tile to the end of the existing domino chain.
Reference: None.
********************************************************************* */
void Layout::addRight(string tile)
{
    dominoChain.push_back(tile);
}

/* *********************************************************************
Function Name: addLeft
Purpose: To extend the game board by adding a validated tile to the left side.
Parameters:
            tile, a string representing the domino. Passed by value.
Return Value: None.
Algorithm:
            1) Prepend the new tile to the beginning of the existing domino chain.
Reference: None.
********************************************************************* */
void Layout::addLeft(string tile)
{
    dominoChain.push_front(tile);
}

/* *********************************************************************
Function Name: clearChain
Purpose: To remove all tiles from the board, resetting the layout for
         a new round.
Parameters: None.
Return Value: None.
Algorithm:
            1) Clear the domino chain container of all entries.
Reference: None.
********************************************************************* */
void Layout::clearChain()
{
    dominoChain.clear();
}

/* *********************************************************************
Function Name: getChain
Purpose: To retrieve the current sequence of tiles on the board for
         display or logic checks.
Parameters: None.
Return Value: A deque of strings representing the domino sequence.
Algorithm:
            1) Return the internal collection of tiles representing the board.
Reference: None.
********************************************************************* */
deque<string> Layout::getChain() const
{
    return dominoChain;
}