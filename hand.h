#pragma once

#include <iostream>
#include <vector>
#include <string>

/**
 * @class Hand
 * @brief Management class for a player's collection of domino tiles.
 * * This class acts as a wrapper for a dynamic collection of strings representing
 * dominoes (e.g., "6-6"). It provides high-level operations for hand manipulation,
 * such as adding/removing tiles, and integrates with the Cereal library for
 * persistent game state storage.
 */

class Hand
{
    std::vector<std::string> tiles; ///< the tiles in the hand currently

public:


    /**
     * @brief Cereal serialization function.
     * Maps the internal 'tiles' vector to the JSON key "tiles" during save/load.
     * @param archive The archive object (JSON) being read from or written to.
     */
    

    /** @brief Default constructor. Initializes an empty hand. */
    Hand();

    /** @brief Outputs the current hand to the standard console. */
    void displayHand();

    /** @brief Utility check to determine if the player has any tiles left. */
    bool isEmptyHand();

    /** * @brief Retrieves a tile string based on its position in the vector.
     * @param index The zero-based index of the tile.
     * @return std::string The tile string (e.g., "1-2").
     */
    std::string getTileByIndex(int index) const;

    int getIndexByTile(std::string tile) const;

    /** @brief Removes a tile from the hand using its vector index. */
    void removeTile(int tileDex);

    bool hasTile(std::string targetTile);

    /** @brief Clears all tiles from the hand, usually at the end of a round. */
    void emptyHand();

    /** @brief Appends a single tile string to the existing hand. */
    void addTile(std::string tile);

    /** @brief Replaces the entire hand with a new set of tiles. Used for dealing. */
    void setTiles(std::vector<std::string> deal);

    /** @brief Returns a copy of the hand's tile collection. */
    std::vector<std::string> getHandTiles() const;
};
