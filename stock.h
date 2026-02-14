#pragma once

#include <vector>
#include <string>

#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>

/**
 * @class Stock
 * @brief Manages the collection of all dominoes not currently in a player's hand.
 * * This class handles the initialization of a standard double-six set (28 tiles),
 * the shuffling logic using a Fisher-Yates approach, and the distribution
 * of tiles via dealing or drawing.
 */
class Stock
{
private:
    std::vector<std::string> boneyard; ///< Internal storage for available dominoes.
    static constexpr short TILES = 8;  ///< Number of tiles to be dealt per player at round start.
    const short MAXPIP = 6;

public:
    Stock();

    /**
    * @brief Cereal serialization for the boneyard.
    * Crucial for ensuring the deck remains in the same order upon loading.
    */

    void setBoneyard(std::vector<std::string> tiles)
    {
        boneyard = tiles;
    }

    /** @brief Prints all remaining tiles in the boneyard to the console. */
    void display() const;

    /** @brief Randomizes the order of tiles using a Fisher-Yates shuffle. */
    void shuffle();
    /** * @brief Removes and returns the top tile from the boneyard.
     * @return std::string The tile value, or empty string if boneyard is empty.
     */

    std::string drawTile();

    /** * @brief Deals a starting hand of tiles to a player.
     * @return std::vector<std::string> A collection of 8 tiles (or fewer if stock is low).
     */
    std::vector<std::string> deal();

    /** @brief Returns a copy of the boneyard vector for game logic checks. */
    std::vector<std::string> getBoneyard() const;

    /** @brief Resets the boneyard to a full, shuffled 28-tile set for a new round. */
    void reset();
};
