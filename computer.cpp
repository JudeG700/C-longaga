#pragma once
#include "computer.h"
#include "hand.h"   // REQUIRED
#include "stock.h"
#include <utility>
#include <set>
#include <vector>
#include "round.h"
using namespace std;


/* *********************************************************************
Function Name: Computer (Constructors)
Purpose: To initialize the Computer player object, either with default values
         or by assigning a specific starting hand.
Parameters:
            hand, a Hand object. Passed by value.
Return Value: None.
Algorithm:
            1) Set the player's identity to "Computer".
            2) Assign the provided hand (if applicable) to the internal member.
Reference: None.
********************************************************************* */
Computer::Computer()
{

}


Computer::Computer(Hand hand)
{
    this->hand = hand;
}
std::string Computer::returnID() const
{
    return ID;
}

/* *********************************************************************
Function Name: isDouble
Purpose: To determine if a specific tile is a "Double" (e.g., 6-6).
Parameters:
            a, an integer representing the first pip value.
            b, an integer representing the second pip value.
Return Value: Boolean; true if the values are equal.
Reference: None.
********************************************************************* */
bool Computer::isDouble(int a, int b) {
    return a == b;
}

/* *********************************************************************
Function Name: tileWeight
Purpose: To calculate the total point value (pip sum) of a single tile.
Parameters:
            a, first pip value (integer).
            b, second pip value (integer).
Return Value: Integer representing the total pips.
Reference: None.
********************************************************************* */
int Computer::tileWeight(int a, int b) {
    return a + b;
}

/* *********************************************************************
Function Name: scoreTile
Purpose: To evaluate the strategic desirability of playing a specific tile
         using a heuristic scoring system.
Parameters:
            a, first pip value (integer).
            b, second pip value (integer).
            leftEnd, current left end of the layout (integer).
            rightEnd, current right end of the layout (integer).
            blockedNumbers, a set of integers representing numbers currently
            blocked for the opponent. Passed by reference.
                  Modified: No. Read-only access for evaluation.
Return Value: Integer; a high score indicates a strategically superior move.
Algorithm:
            1) Start with the base weight (pip sum) to prioritize playing
               heavy tiles early.
            2) Add a bonus if the tile is a double.
            3) Add a bonus if the tile maintains a blocked number state on the
               board to force opponent passes.
Reference: Heuristic scoring logic developed with Gemini AI.
********************************************************************* */
int Computer::scoreTile(
    int a, int b,
    int leftEnd, int rightEnd,
    const std::set<int>& blockedNumbers
) 
{
    int score = 0;

    // 1. Heavy tiles early
    score += tileWeight(a, b);


    // 2. Doubles are valuable
    if (isDouble(a, b))
        score += 10;

    cout << " " << endl;


    return score;
}

/* *********************************************************************
Function Name: parseTile
Purpose: To convert a string representation of a tile (e.g., "5-4") into
         two separate integer values.
Parameters:
            tile, a string. Passed by reference.
                  Modified: No.
Return Value: A pair of integers representing the two sides of the domino.
Algorithm:
            1) Locate the delimiter character ('-').
            2) Extract the substrings before and after the delimiter.
            3) Convert the substrings into integers and return them as a pair.
Reference: String manipulation logic assisted by ChatGPT.
********************************************************************* */
std::pair<int, int> Computer::parseTile(const std::string& tile) {
    size_t dash = tile.find('-');
    if (dash == std::string::npos) return { -1, -1 }; // Safety return

    int left = std::stoi(tile.substr(0, dash));
    int right = std::stoi(tile.substr(dash + 1));
    return { left, right };
}

/* *********************************************************************
Function Name: findPlayableTiles
Purpose: To scan a player's hand and identify which tiles can legally be
         placed on the current board ends.
Parameters:
            playerHand, a Hand object. Passed by reference.
                  Modified: No.
            leftEnd, integer value of the leftmost tile on the board.
            rightEnd, integer value of the rightmost tile on the board.
Return Value: A vector of integers containing the indices of playable tiles.
Algorithm:
            1) Iterate through the collection of tiles in the hand.
            2) For each tile, check if either side matches the left or right
               end of the layout.
            3) If a match exists, save the index of that tile to the playable list.
Reference: Built with chatgpt but underwent multiple changes by me
********************************************************************* */
std::vector<int> Computer::findPlayableTiles(Hand& playerHand, Round& gameRound, int leftEnd, int rightEnd)
{

    std::vector<int> playable;
    std::vector<std::string> tiles = playerHand.getHandTiles();   // works ONLY if getHand returns reference

    bool oppPassed = gameRound.isPassed(0);

    for (int i = 0; i < (int)tiles.size(); i++)
    {
        std::pair<int, int> p = parseTile(tiles[i]);
        int a = p.first;
        int b = p.second;
        bool isDouble = (a == b);

        bool canPlayRight = (a == rightEnd || b == rightEnd);

        // Right side is only valid if (Matches Right) AND (is Double OR Opponent Passed)
        bool canPlayLeft = (a == leftEnd || b == leftEnd) && (isDouble || oppPassed);

        if (canPlayLeft || canPlayRight || isDouble) //what if we add isDouble here?
        {
            /*
            cout << "TILE: " << tiles[i] << endl;
            cout << "canPlayLeft: " << canPlayLeft << endl;
            cout << "canPlayRight: " << canPlayRight << endl;
            cout << "isDouble: " << isDouble << endl;
            cout << "oppPassed: " << oppPassed << endl;
            cout << endl; */
            playable.push_back(i);
        }

    }
    return playable;

}

/* *********************************************************************
Function Name: help
Purpose: To provide the human player with a hint for the best move
         based on computer logic.
Parameters:
            playerHand, a Hand object. Passed by reference.
                  Modified: No.
            gamestock, a Stock object. Passed by value.
            leftEnd, integer board end.
            rightEnd, integer board end.
Return Value: None.
Algorithm:
            1) Identify all tiles in the player's hand that can be legally played.
            2) If no tiles can be played, suggest drawing from the boneyard
               or passing if it is empty.
            3) If tiles are playable, use the heuristic scoring function to
               find the move with the highest strategic value.
            4) Output the recommended tile and board side to the console.
Reference: None 
********************************************************************* */
void Computer::help(Player* player, Stock gamestock, Round gameRound, int leftEnd, int rightEnd)
{
    Move move{};
    const std::set<int> blockedNumbers;


    

    std::vector<int> playable = player->findPlayableTiles(player->getHand(), gameRound, leftEnd, rightEnd);

    if (playable.empty()) {

        if (gamestock.getBoneyard().empty())
        {
            cout << "Boneyard is empty and no playable cards. You have no choice but to pass" << endl;
            return;
        }
        else
        {
            cout << "You have no playable cards right now. It's best you draw" << endl;
            return;
        }

    }


    int bestIndex = -1;
    int bestScore = -1;
    char setSide = 'L';
    char bestSide = 'L';

    for (int idx : playable) {
        
        string tile = playerHand.getTileByIndex(idx);
        pair<int, int> p = parseTile(tile);
        int a = p.first;
        int b = p.second;


        // Check specifically which side(s) this tile fits on
        bool isDouble = (a == b);
        bool fitsLeft = (a == leftEnd || b == leftEnd);
        bool fitsRight = (a == rightEnd || b == rightEnd);

        if (!fitsLeft && !fitsRight) continue;

        int score = scoreTile(a, b, leftEnd, rightEnd, blockedNumbers);

        // If it fits on both, we should ideally pick the side that 
        // benefits us more, but for now, we ensure it's a valid move.
        if (score > bestScore) {
            bestScore = score;
            bestIndex = idx;

            if (fitsLeft) {
                setSide = 'L';
            }
            else if (fitsRight) {
                setSide = 'R';
            }

            

        }
    }

    string tile = playerHand.getTileByIndex(bestIndex);
    cout << "I would recommend " << playerHand.getTileByIndex(bestIndex) << " on side " << bestSide << endl;
    cout << "It has a higher pip value than your other playable tiles, ";
    if (tile[0] == tile[2])
    {
        cout << "and is a double, which can be placed anywhere on the layout and help you maintain control " << endl;
    }
    else
    {
        cout << "which you want to get rid of. " << endl;
        cout << "Holding higher pip values in your ha will give your opponent a higher score if you lose" << endl;
    }
}



/* *********************************************************************
Function Name: takeTurn
Purpose: To automate the decision-making process for the AI's turn.
Parameters:
            gameStock, a Stock object. Passed by value.
            leftEnd, integer board end.
            rightEnd, integer board end.
Return Value: A Move structure containing the chosen tile, side, and action status.
Algorithm:
            1) Search the computer's hand for legal moves.
            2) If no moves are possible, check if a tile can be drawn from
               the boneyard.
            3) If boneyard is empty, set the action status to "pass".
            4) If moves are possible, evaluate the "score" of each playable
               tile and select the highest.
            5) Return the final move selection.
Reference: Computer turn state-machine logic assisted by chatgpt
********************************************************************* */
Move Computer::takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd)

{
    Move move{};
    const std::set<int> blockedNumbers;

    
    cout << "Finding playable tiles... " << endl;
    std::vector<int> playable = findPlayableTiles(hand, gameRound, leftEnd, rightEnd);

    
    //If there are no predicted playable tiles, the computer will draw
    if (playable.empty()) {


        //before drawing, check if boneyard is full

        vector<string> boneyard = gameStock.getBoneyard();
        if (boneyard.empty())
        {
            cout << "Boneyard empty. Can't draw. Passing for this round." << endl;
            move.draw = false;

            //left with no choice but to pass 

            move.passed = true;
        }
        else
        {
            cout << "No matching tiles. Proceeding with drawing a tile..." << endl;
            move.draw = true;
        }
        return move;
    }


    int bestIndex = -1;
    int bestScore = -1;
    char setSide = 'R';
    char bestSide = 'R';

    cout << "Selecting highest value tile in list of playable tiles" << endl;
    

    for (int idx : playable) {
        string tile = hand.getTileByIndex(idx);
        pair<int, int> p = parseTile(tile);
        int a = p.first;
        int b = p.second;

        bool isDouble = (a == b);
        

        // Computer can ALWAYS play on Right (its own side).
        bool fitsRight = (a == rightEnd || b == rightEnd);

        bool humanPassed = gameRound.isPassed(0); // 0 is usually Human
        // Computer can ONLY play on Left (Human's side) IF it's a double OR Human passed.
        bool fitsLeft = (a == leftEnd || b == leftEnd) && ( humanPassed);

        if (isDouble)
        {
            fitsLeft = true;
            fitsRight = true;
        }

        if (!fitsLeft && !fitsRight) continue; // Skip if this tile is now "illegal"

        if (fitsRight) {
            setSide = 'R';
        }
        else {
            setSide = 'L';
        }

        //This ensures that even though doubles match both sides, it will pick left first to
        //intentionally screw over the opponent
        if (isDouble && fitsLeft)
        {
            setSide = 'L';
        }

        int score = scoreTile(a, b, leftEnd, rightEnd, blockedNumbers);


        if (score > bestScore) {
            bestScore = score;
            bestIndex = idx;



            // Priority: If it fits on its own side (Right), take it. 
            // Otherwise, take the Left if allowed.
            
        }
    }

    move.tileIndex = bestIndex;
    move.side = bestSide;
    move.draw = false; // We found a move, so don't draw
    //move.passed = false;
    return move;

}
