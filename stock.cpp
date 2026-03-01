/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

#include "stock.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

/* *********************************************************************
Function Name: Stock (Constructor)
Purpose: To create a complete set of 28 double-six domino tiles.
Parameters: None.
Return Value: None.
Algorithm:
            1) Create all possible combinations of tiles from 0-0 up to 6-6.
            2) Ensure each tile pair is unique.
            3) Initialize the random number generator for future shuffling.
Reference: Chatgpt assisted in building function
********************************************************************* */
Stock::Stock()
{

    for (int i = 0; i <= MAX_PIP_VALUE; i++)
    {
        for (int j = i; j <= MAX_PIP_VALUE; j++)
        {
            boneyard.push_back(to_string(i) + "-" + to_string(j));
        }
    }

    //randomize tiles
    srand(static_cast<unsigned>(time(nullptr)));
}


/* *********************************************************************
Function Name: display
Purpose: To show all tiles currently remaining in the boneyard.
Parameters: None.
Return Value: None.
Algorithm:
            1) Traverse the set of remaining tiles.
            2) Output each tile representation to the console.
Reference: Chatgpt assisted in building function
********************************************************************* */
void Stock::display() const
{
    for (const auto& tile : boneyard)
    {
        cout << tile << " ";
    }
    cout << endl;
}

/* *********************************************************************
Function Name: shuffle
Purpose: To randomize the order of the tiles in the boneyard to ensure
         fairness in drawing.
Parameters: None.
Return Value: None.
Algorithm:
            1) Start from the last tile in the boneyard.
            2) Randomly select any tile that comes before it.
            3) Swap the positions of the two tiles.
            4) Repeat this moving backwards until the entire set is randomized.
Reference: Standard Fisher-Yates shuffle logic from chatgpt
********************************************************************* */
void Stock::shuffle()
{
    for (int i = boneyard.size() - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(boneyard[i], boneyard[j]);
    }
}

/* *********************************************************************
Function Name: drawTile
Purpose: To remove a single tile from the boneyard and provide it to
         a player.
Parameters: None.
Return Value: A string representing the drawn domino tile.
Algorithm:
            1) Verify if the boneyard contains any tiles.
            2) Retrieve the tile from the top of the boneyard.
            3) Remove that tile from the boneyard so it cannot be drawn again.
Reference: Chatgpt assisted in building function
********************************************************************* */
string Stock::drawTile()
{
    if (boneyard.empty())
        return "";

    //draw from front of boneyard
    string tile = boneyard.front();
    if (!boneyard.empty()) {
        boneyard.erase(boneyard.begin()); 
    }

    return tile;
}

/* *********************************************************************
Function Name: deal
Purpose: To provide a starting hand of tiles to a player at the beginning
         of a round.
Parameters: None.
Return Value: A vector of strings containing the dealt tiles.
Algorithm:
            1) Determine the required hand size (8 tiles).
            2) Repeatedly draw tiles from the boneyard until the hand is full
               or the boneyard is empty.
            3) Return the collection of tiles to the player.
Reference: Chatgpt assisted in building function
********************************************************************* */
vector<string> Stock::deal()
{
    vector<string> hand;

    //deal 8 cards or whatever the deal count is
    for (int i = 0; i < INITIAL_DEAL_COUNT && !boneyard.empty(); i++)
    {
        hand.push_back(boneyard.back());
        //boneyard.erase(boneyard.begin());
        boneyard.pop_back();
    }

    return hand;
}

/* *********************************************************************
Function Name: getBoneyard
Purpose: To retrieve the current collection of tiles for logic checks.
Parameters: None.
Return Value: A vector of strings containing the remaining tiles.
Reference: None.
********************************************************************* */
vector<string> Stock::getBoneyard() const
{
    return boneyard;
}

/* *********************************************************************
Function Name: getBoneyard
Purpose: To retrieve the current collection of tiles for logic checks.
Parameters: vector<string> tiles passed by values. A chain of tiles used
to initialize the boneyard for when a loaded game is called.
Return Value: A vector of strings containing the remaining tiles.
Reference: None.
********************************************************************* */

void Stock::setBoneyard(std::vector<std::string> tiles)
{
    boneyard = tiles;
}

/* *********************************************************************
Function Name: reset
Purpose: To restore the boneyard to its original full state and reshuffle
         for a new round.
Parameters: None.
Return Value: None.
Algorithm:
            1) Clear any remaining tiles from the current boneyard.
            2) Regenerate the full set of 28 unique domino tiles.
            3) Shuffle the tiles to provide a new random distribution.
Reference: Chatgpt assisted in building function
********************************************************************* */
void Stock::reset()
{
    empty();

    //add new tiles to cleared boneyard and then shuffle
    for (int i = 0; i <= MAX_PIP_VALUE; i++)
    {
        for (int j = i; j <= MAX_PIP_VALUE; j++)
        {
            boneyard.push_back(to_string(i) + "-" + to_string(j));
        }
    }

    shuffle();
}

void Stock::empty()
{
    boneyard.clear();

}