#pragma once
#include "hand.h"
#include "player.h"
#include <iostream>
#include "stock.h"
//#include "round.h"


class Round;

/**
 * @class Human
 * @brief Represents the human participant in the Longaga game.
 * * This class inherits from the Player base class. It handles user interactions,
 * capturing input from the console to facilitate game actions such as playing a
 * tile, drawing from the boneyard, passing a turn, or requesting AI assistance.
 */
class Human : public Player {

    std::string ID = "Human"; ///< Human's identifier

public:

    /** @brief Default constructor. */
    Human();

    /** * @brief Constructor that initializes the player with a specific hand.
     * @param humanHand The initial set of tiles dealt to the user.
     */
    Human(Hand humanHand);

    ~Human(){};

    /** @brief Returns "Human" for display and logic identification. */
    std::string returnID() const override;

    /** * @brief Facilitates the human's turn via console input.
         * * Implements the pure virtual function from Player. It prompts the user
         * for a choice (Play, Draw, Pass, or Help) and validates the inputs
         * (indices and board sides) before returning a Move structure.
         * * @param gameStock Reference to the current boneyard.
         * @param leftEnd Current playable value on the layout's left.
         * @param rightEnd Current playable value on the layout's right.
         * @return Move A struct containing the validated user decision/s.
         */    
    Move takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd) override;  // declared here

    std::vector<int> findPlayableTiles(Hand& playerHand, Round& gameRound, int leftEnd, int rightEnd);

    std::pair<int, int> parseTile(const std::string& tile);


};
