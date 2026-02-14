#include "hand.h"


/* *********************************************************************
Function Name: Hand (Constructor)
Purpose: To initialize an empty collection of domino tiles for a player.
Parameters: None.
Return Value: None.
Algorithm:
            1) Initialize the internal tile container to an empty state.
Reference: None.
********************************************************************* */
Hand::Hand() {}

/* *********************************************************************
Function Name: displayHand
Purpose: To present the current set of dominoes held by a player to
         the console.
Parameters: None.
Return Value: None.
Algorithm:
            1) Traverse the player's collection of tiles.
            2) Output each tile representation (e.g., "3-4") followed by
               a space for readability.
Reference: None.
********************************************************************* */
void Hand::displayHand()
{
    std::cout << "Hand: ";
    for (int i = 0; i < tiles.size(); i++)
    {
        std::cout << tiles[i] << " ";
    }
}

/* *********************************************************************
Function Name: isEmptyHand
Purpose: To determine if a player has run out of tiles (a "domino" condition).
Parameters: None.
Return Value: Boolean; true if the player holds no tiles.
Algorithm:
            1) Check the count of tiles currently in the player's possession.
            2) Return true if the count is zero.
Reference: None.
********************************************************************* */
bool Hand::isEmptyHand()
{
    return tiles.empty();
}

bool Hand::hasTile(std::string targetTile) {
    // We check both "6-6" and "6-6" (and in case of non-doubles, "5-6" and "6-5")
    std::string flipped = "";
    flipped += targetTile[2];
    flipped += '-';
    flipped += targetTile[0];

    for (const std::string& tile : tiles) {
        if (tile == targetTile || tile == flipped) {
            return true;
        }
    }
    return false;
}

/* *********************************************************************
Function Name: getTileByIndex
Purpose: To retrieve a specific domino from the player's hand based on
         its position.
Parameters:
            index, an integer representing the selection position.
Return Value: A string representing the chosen domino tile.
Algorithm:
            1) Access the tile at the specified location within the collection.
            2) Return the string value of that tile.
Reference: chatgpt built this
********************************************************************* */
std::string Hand::getTileByIndex(int index) const
{
    return tiles[index];
}

/* *********************************************************************
Function Name: removeTile
Purpose: To discard a tile from the player's hand after it has been
         played on the board.
Parameters:
            tileDex, an integer. The position index of the tile to discard.
Return Value: None.
Algorithm:
            1) Locate the specific tile in the collection using the index.
            2) Permanently remove the tile so it is no longer in the
               player's possession.
Reference: None
********************************************************************* */
void Hand::removeTile(int tileDex)
{
    tiles.erase(tiles.begin() + tileDex);
}

/* *********************************************************************
Function Name: emptyHand
Purpose: To clear all tiles from the player's possession, typically
         between game rounds.
Parameters: None.
Return Value: None.
Algorithm:
            1) Remove every tile currently held in the collection.
Reference: None
********************************************************************* */
void Hand::emptyHand()
{
    tiles.clear();
}

/* *********************************************************************
Function Name: addTile
Purpose: To add a new domino to the player's hand, such as when
         drawing from the boneyard.
Parameters:
            tile, a string representing the domino to be added.
Return Value: None.
Algorithm:
            1) Receive the tile string.
            2) Append the tile to the end of the player's current collection.
Reference: None
********************************************************************* */
void Hand::addTile(std::string tile)
{
    tiles.push_back(tile);
}

/* *********************************************************************
Function Name: setTiles
Purpose: To replace the player's entire hand with a new set of tiles.
Parameters:
            deal, a vector of strings representing a new hand.
            Passed by value.
Return Value: None.
Algorithm:
            1) Accept a new collection of tiles (e.g., from the initial deal).
            2) Overwrite the current hand with this new set.
Reference: None
********************************************************************* */
void Hand::setTiles(std::vector<std::string> deal)
{
    tiles = deal;
}

/* *********************************************************************
Function Name: getHandTiles
Purpose: To provide the full set of currently held tiles for game
         logic processing.
Parameters: None.
Return Value: A vector of strings containing all dominoes in the hand.
Reference: None.
********************************************************************* */
std::vector<std::string> Hand::getHandTiles() const
{
    return tiles;
}
