/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

#include "computer.h"
#include "hand.h"
#include "stock.h"
#include <utility>
#include <set>
#include <vector>
#include "round.h"
#include <iostream>

using namespace std;




/* *********************************************************************
Function Name: returnID
Purpose: To retrieve the player's unique identifier ("Computer").
Parameters: None.
Return Value: String ID.
********************************************************************* */
std::string Computer::returnID() const {
    return ID;
}

/* *********************************************************************
Function Name: isDouble
Purpose: To determine if a specific tile is a "Double" (e.g., 6-6).
Parameters:
   a, an integer representing the first pip value.
   b, an integer representing the second pip value.
Return Value: Boolean; true if the values are equal.
********************************************************************* */
bool Computer::isDouble(int a, int b) const {
    return a == b;
}

/* *********************************************************************
Function Name: tileWeight
Purpose: To calculate the total point value (pip sum) of a single tile.
Parameters:
   a, first pip value (integer).
   b, second pip value (integer).
Return Value: Integer representing the total pips.
********************************************************************* */
int Computer::tileWeight(int a, int b) const {
    return a + b;
}

/* *********************************************************************
Function Name: scoreTile
Purpose: To evaluate the strategic desirability of a move using heuristics.
Parameters:
   a, first pip value.
   b, second pip value.
   leftEnd, current left board end.
   rightEnd, current right board end.
   pickedSide, the board side being evaluated ('L' or 'R').
   player, string ID of the player being evaluated.
Return Value: Integer score; higher is better.
Algorithm:
   1) Use base pip sum as the starting score (prioritize dumping heavy tiles).
   2) Add a bonus for doubles.
   3) Add a strategic bonus for playing doubles on the opponent's side.'
Reference: Google gemini assisted
********************************************************************* */
int Computer::scoreTile(int a, int b, int leftEnd, int rightEnd, char pickedSide, string player) {
    int score = 0;

    // Prioritize heavy tiles to minimize potential end-of-round penalty
    score += tileWeight(a, b);

    // Strategic valuation for doubles
    if (isDouble(a, b)) {
        score += 10;

        // Encourage the AI to play doubles on the opponent's side
        if (pickedSide == 'L' && player == "Computer") {
            score += 10;
        }
        //Encourage the player to play doubles on their opponent's side
        else if (pickedSide == 'R' && player == "Human") {
            score += 10;
        }
    }
    return score;
}

/* *********************************************************************
Function Name: parseTile
Purpose: To convert a string representation (e.g., "5-4") into two integers.
Parameters:
   tile, a constant string reference.
Return Value: A pair of integers.
Reference: Assistance from chatgpt
********************************************************************* */
std::pair<int, int> Computer::parseTile(const std::string& tile) {
    size_t dash = tile.find('-');
    if (dash == std::string::npos) return { -1, -1 };

    int left = std::stoi(tile.substr(0, dash));
    int right = std::stoi(tile.substr(dash + 1));
    return { left, right };
}

/* *********************************************************************
Function Name: findPlayableTiles
Purpose: To scan the hand and identify legal moves based on Longana rules.
Parameters:
   hand, a Hand object passed by value.
   gameRound, a Round object reference.
   leftEnd, current left board end.
   rightEnd, current right board end.
Return Value: Vector of PlayableOption structs.
Algorithm:
   1) Identify if the human player has passed to unlock the opponent side.
   2) Loop through tiles; verify if they match the required ends.
   3) Apply special rules for doubles (playable on any side).
Reference: Assistance from gemini
********************************************************************* */
std::vector<Player::PlayableOption> Computer::findPlayableTiles(Hand hand, Round& gameRound, int leftEnd, int rightEnd) {
    
    std::vector<Player::PlayableOption> playable;
    std::vector<std::string> tiles = hand.getHandTiles();

    const int HUMAN_PLAYER_INDEX = 0;
    bool humanPassed = gameRound.isPassed(HUMAN_PLAYER_INDEX);

    for (int i = 0; i < (int)tiles.size(); i++) {
        std::pair<int, int> p = parseTile(tiles[i]);
        bool isDoubleTile = isDouble(p.first, p.second);

        bool matchesLeft = (p.first == leftEnd || p.second == leftEnd);
        bool matchesRight = (p.first == rightEnd || p.second == rightEnd);

        // Computer side (Right)
        if (matchesRight) {
            playable.push_back({ i, 'R' });
        }

        // Opponent side (Left) - requires double or human pass
        if (matchesLeft && (isDoubleTile || humanPassed)) {
            playable.push_back({ i, 'L' });
        }
    }
    return playable;
}

/* *********************************************************************
Function Name: help
Purpose: Suggests the optimal move for the human player.
Parameters:
   player, a Player pointer.
   gamestock, a Stock object.
   gameRound, a Round object.
   leftEnd, rightEnd, board values.
Algorithm:
   1) Find all legal moves for the human.
   2) If none, recommend drawing or passing.
   3) Otherwise, score each move and suggest the highest-scoring option.
Reference: Assistance from gemini
********************************************************************* */
void Computer::help(Player* player, Stock gamestock, Round gameRound, int leftEnd, int rightEnd) {
    //get all playable tiles
    std::vector<Player::PlayableOption> playableTiles = player->findPlayableTiles(player->getHand(), gameRound, leftEnd, rightEnd);

    //if there are no playable tiles
    if (playableTiles.empty()) {
        if (gamestock.getBoneyard().empty()) {
            cout << "The boneyard is empty and there's no playable tiles. You must pass." << endl;
        }
        else {
            cout << "No playable tiles. It's best to draw." << endl;
        }
        return;
    }


    //default to left side for humans
    int bestIndex = -1;
    int bestScore = -1;
    char bestSide = 'L';


    for (const auto& option : playableTiles) {
        string tile = player->getHand().getTileByIndex(option.index);
        pair<int, int> pips = parseTile(tile);

        //use an invisible score to find best rated tile
        int currentScore = scoreTile(pips.first, pips.second, leftEnd, rightEnd, option.side, player->returnID());

        if (currentScore > bestScore) {
            bestScore = currentScore;
            bestIndex = option.index;
            bestSide = option.side;
        }
    }

    //there will be no playable tiles
    if (bestIndex != -1) {
        string recommendedTile = player->getHand().getTileByIndex(bestIndex);
        cout << "Recommendation: " << recommendedTile << " on side " << bestSide << endl;

        const int COMPUTER_INDEX = 1;
        if (bestSide == 'R' && gameRound.isPassed(COMPUTER_INDEX)) {
            cout << "The opponent has passed! Place a tile on their side R to disrupt their chain!." << endl;
        }

        if (recommendedTile[0] == recommendedTile[2]) {
            cout << "Doubles can be placed on both sides as long as they match." << endl;
        }
        else {
            cout << "High pip values should be played as soon as possible to reduce the amount of points your opponent receives." << endl;
        }
    }
    
}

/* *********************************************************************
Function Name: takeTurn
Purpose: Main AI logic for choosing the computer's move.
Return Value: A Move structure containing the chosen action.
Algorithm:
   1) Generate legal moves.
   2) Draw if no moves are possible.
   3) Score all available moves and execute the best one.
********************************************************************* */
Move Computer::takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd) {
    Move move{};
    std::vector<Player::PlayableOption> playableTiles = findPlayableTiles(hand, gameRound, leftEnd, rightEnd);

    if (playableTiles.empty()) {
        if (gameStock.getBoneyard().empty()) {
            move.draw = false;
            move.passed = true;
        }
        else {
            move.draw = true;
        }
        return move;
    }

    //default to left side for humans
    int bestIndex = -1;
    int bestScore = -1;
    char bestSide = 'R';

    for (const auto& option : playableTiles) {
        string tile = hand.getTileByIndex(option.index);
        pair<int, int> p = parseTile(tile);
        int currentScore = scoreTile(p.first, p.second, leftEnd, rightEnd, option.side, returnID());

        if (currentScore > bestScore) {
            bestScore = currentScore;
            bestIndex = option.index;
            bestSide = option.side;
        }
    }

    move.tileIndex = bestIndex;
    move.side = bestSide;
    move.draw = false;
    return move;
}