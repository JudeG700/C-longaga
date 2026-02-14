#pragma once
#include "hand.h"
#include <vector>
#include "move.h"
#include "stock.h"
//#include "round.h"
#include <iostream>
#include <set>


class Round;

/**
 * @class Player
 * @brief Abstract Base Class providing the core interface for all game participants.
 * * The Player class defines the shared attributes (Hand, Score, ID) and the
 * essential behaviors required for both Human and AI players. By using a
 * pure virtual function for takeTurn, this class enforces a consistent
 * gameplay interface while allowing for polymorphic behavior in the main loop.
 */
class Player {


protected:

    Hand hand;              ///< The internal collection of tiles owned by the player.
    int score = 0;          ///< The player's current total score for the tournament.
    std::string ID = "Player"; ///< Default identifier, overridden by derived classes.

public:
    
    /** @brief Default constructor. Initializes a player with a zero score. */
    Player();

    /** @brief Virtual destructor to ensure proper cleanup of derived objects. */
    virtual ~Player() {}

    /**
     * @brief Pure virtual function to be implemented by Human and Computer.
     * * This method acts as the entry point for player logic. It requires
     * visibility of the current boneyard (Stock) and the ends of the
     * layout to determine valid moves.
     * * @param gameStock The current state of the boneyard for drawing tiles.
     * @param leftEnd The numeric value of the layout's left-most open pip.
     * @param rightEnd The numeric value of the layout's right-most open pip.
     * @return Move A structure detailing the chosen tile and board side.
     */
    virtual Move takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd) = 0;

    /** @brief Returns a copy of the player's Hand object. */
    Hand getHand();

    virtual std::string returnID() const;

    /** @brief Increments the player's cumulative tournament score. */
    void addPoints(int points);

    /** @brief Returns the current score as an integer. */
    int getScore() const;

    /** @brief Returns the ID string ("Human" or "Computer"). */
    
    /** @brief Instructs the internal Hand object to delete a tile at a specific index. */
    void removeTile(int integer);

    /** @brief Adds a new tile (from the stock or deal) to the player's hand. */
	void addTile(std::string tile);

    /** @brief Clears all tiles from the internal Hand container. */
    void emptyHand();

    /** @brief Overwrites the hand with a new collection of tiles. */
    void setTiles(std::vector<std::string> deal);

    /** @brief Returns the vector of tile strings for display/logic. */
    std::vector<std::string> getHandTiles() const;


};

