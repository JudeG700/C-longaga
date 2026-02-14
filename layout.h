#pragma once

#include <iostream>
#include <deque>
#include <string>

// Including these now makes sure they are ready when you uncomment cereal later
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/array.hpp>
#include <cereal/types/deque.hpp>

class Layout {
private:
    std::deque<std::string> dominoChain; ///< The domino chain formed by players

public:
    Layout() {}

    /**
        * @brief Cereal serialization for the domino layout.
        * Maps the deque to the "domino_chain" key in JSON.
        */

 
    /** @brief Appends a tile to the right-hand side of the layout. */
    void addRight(std::string tile);

    bool isEmpty()
    {
        return dominoChain.empty();
    }

    /** @brief Appends a tile to the left-hand side of the layout. */
    void addLeft(std::string tile);

    /** * @brief Returns the pip value available on the left-most tile.
        * @return Integer value of the left end, or -1 if empty.
        */
    int returnLeft();

    /** * @brief Returns the pip value available on the right-most tile.
        * @return Integer value of the right end, or -1 if empty.
        */
    int returnRight();

    /** @brief Clears all tiles from the board for a new round. */
    void clearChain();

    /** @brief Returns a copy of the current domino sequence. */
    std::deque<std::string> getChain() const;
    };