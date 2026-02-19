/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

#pragma once
#include "hand.h"
#include <vector>
#include "move.h"
#include "stock.h"
#include "player.h"
#include "round.h"
#include <iostream>
#include <set>



/* *********************************************************************
Function Name: getHand
Purpose: To return a copy of the player's Hand object.
Parameters: none
Return Value: Hand, a copy of the private hand member.
Algorithm:
            1) Return the hand object by value per project constraints.
Reference: none
********************************************************************* */
Hand Player::getHand() const
{
    return hand;
}

/* *********************************************************************
Function Name: addPoints
Purpose: To update the cumulative tournament score.
Parameters:
            points, an integer. The number of pips from the losing hand.
Return Value: none
Algorithm:
            1) Add the incoming points value to the current score member.
Reference: none
********************************************************************* */
void Player::addPoints(int points)
{
    score += points;
}


/* *********************************************************************
Function Name: getScore
Purpose: To retrieve the current integer score for tournament tracking.
Parameters: none
Return Value: The current score, an integer.
Algorithm:
            1) Return the value stored in the score variable.
Reference: none
********************************************************************* */
int Player::getScore() const
{
    return score;
} 


/* *********************************************************************
Function Name: returnID
Purpose: To retrieve the string ID for the player.
Parameters: none
Return Value: A string (e.g., "Human" or "Computer").
Reference: none
********************************************************************* */
std::string Player::returnID() const
{
    return ID;
}

/* *********************************************************************
Function Name: emptyHand
Purpose: To clear all tiles in a hand for round reset.
Parameters: none
Return Value: none
Reference: none
********************************************************************* */
void Player::emptyHand()
{
    hand.emptyHand();
}

/* *********************************************************************
Function Name: removeTile
Purpose: To remove a specific tile from the hand by index.
Parameters:
            integer, an integer. The index of the tile to be removed.
Return Value: none
Algorithm:
            1) Delegate removal logic to the hand object.
Reference: none
********************************************************************* */
void Player::removeTile(int integer)
{
    hand.removeTile(integer);
}

/* *********************************************************************
Function Name: addTile
Purpose: To append a single tile to the player's hand.
Parameters:
            tile, a string representation of the domino.
Return Value: none
Algorithm:
            1) Call the addTile() method on the internal hand object.
Reference: none
********************************************************************* */
void Player::addTile(std::string tile)
{
    hand.addTile(tile);
}

/* *********************************************************************
Function Name: setTiles
Purpose: To populate the hand with a new vector of tiles.
Parameters:
            deal, a vector of strings. The new set of dominoes.
Return Value: none
Reference: none
********************************************************************* */
void Player::setTiles(std::vector<std::string> deal)
{
    hand.setTiles(deal);
}


/* *********************************************************************
Function Name: getHandTiles
Purpose: To return the vector of tiles from the hand object.
Parameters: none
Return Value: std::vector<std::string>, the current tiles.
Algorithm:
            1) Retrieve the vector from the hand object and return it.
Reference: none
********************************************************************* */
std::vector<std::string> Player::getHandTiles() const
{
    return hand.getHandTiles();
}
