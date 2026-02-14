#pragma once
#include "player.h"
#include "hand.h"
#include "stock.h"
//#include "round.h"
#include <vector>
#include <string>
#include <set>


/**
 * @class Computer
 * @brief Represents the AI opponent in the Longaga game.
 * * This class inherits from Player and implements automated decision-making
 * logic for tile selection based on a weighted scoring heuristic.
 */

//Since player is initialized in round class, player class will throw a fit when I include round.h so this is the only way to get this working
class Round;

class Computer : public Player {

private:

    std::string ID = "Computer"; ///< Computer's identifier
    //Hand hand; ///< The computer's hand with stock


    /**
    * @brief Helper to convert string representation (e.g., "6-6") to numeric pairs.
    */

    std::pair<int, int> parseTile(const std::string& tile); 

    /**
     * @brief Scans the current hand for any tiles that match the layout ends.
     */
    std::vector<int> findPlayableTiles(Hand& playerHand, Round& gameRound, int leftEnd, int rightEnd);

public:
    
    /** @brief Default constructor. */
    Computer();

    /** * @brief Constructor that initializes the player with a specific hand.
    * @param humanHand The initial set of tiles dealt to the user.
    */
    Computer(Hand hand);

    ~Computer() {};


    /** @brief Returns true if the tile values match (a double). */
    bool isDouble(int a, int b);

    /** @brief Returns the sum of the pips (tile weight) for strategic sorting. */
    int tileWeight(int a, int b);

    /**
     * @brief Calculates a heuristic score for a potential move.
     * Used to compare which playable tile provides the best strategic advantage.
     */
    int scoreTile(int a, int b, int leftEnd, int rightEnd, const std::set<int>& blockedNumbers);

    /**
     * @brief The core AI logic. Evaluates the hand and returns the optimal Move.
     * Decisions prioritize high-weight tiles and doubles.
     */
    Move takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd) override;


    /**
     * @brief Suggests a move for the Human player using the Computer's scoring logic.
     */

    void help(Player* player, Stock gamestock, Round gameRound, int leftEnd, int rightEnd);

    /** @brief Returns "Computer" to identify the player type. */
    std::string returnID() const override;
};