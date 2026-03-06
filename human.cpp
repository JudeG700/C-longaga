/************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS - 366 OPL
* Date : 2 / 13 / 2026
* ***********************************************************
*/

#include "human.h"
#include <limits>
#include <string>
#include <iostream>
#include "Computer.h"
#include "round.h"
#include <iterator>

using namespace std;

/* *********************************************************************
Function Name: returnID
Purpose: To retrieve the player's unique identifier.
Parameters: None.
Return Value: The string ID of the human player.
Algorithm:
   1) Return the internal ID member variable.
Reference: None.
********************************************************************* */
std::string Human::returnID() const {
    return ID;
}

/* *********************************************************************
Function Name: parseTile
Purpose: To convert a string representation of a tile into two numeric values.
Parameters:
   tile, a constant string passed by reference. Represents the tile (e.g., "5-4").
Return Value: A pair of integers representing the two pip values.
Algorithm:
   1) Find the position of the dash delimiter.
   2) Extract the numeric substring before the dash and convert to integer.
   3) Extract the numeric substring after the dash and convert to integer.
   4) Return the pair of pips.
Reference: Logic for string parsing assisted by Gemini AI.
********************************************************************* */
std::pair<int, int> Human::parseTile(const std::string& tile) {
    size_t dash = tile.find('-');
    // Return sentinel values if string format is incorrect
    if (dash == std::string::npos) return { -1, -1 };

    int left = std::stoi(tile.substr(0, dash));
    int right = std::stoi(tile.substr(dash + 1));
    return { left, right };
}

/* *********************************************************************
Function Name: findPlayableTiles
Purpose: To identify all valid moves currently available in the player's hand.
Parameters:
   hand, a Hand object passed by value. Contains the current tiles.
   gameRound, a Round object passed by reference. Used to check pass status.
   leftEnd, an integer representing the leftmost value on the board.
   rightEnd, an integer representing the rightmost value on the board.
Return Value: A vector of PlayableOption structures (index and side).
Algorithm:
   1) Check if the opponent has passed to determine legal play sides.
   2) Iterate through every tile in the player's hand.
   3) Check if a tile matches the board's left end or is a double.
   4) Check if a tile matches the board's right end (legal only if double or opponent passed).
   5) Store and return all valid tile-index/side combinations.
Reference: modeling algorithm for finding playable tiles and building return struct assisted by gemini and chatgpt
********************************************************************* */
std::vector<Player::PlayableOption> Human::findPlayableTiles(Hand hand, Round& gameRound, int leftEnd, int rightEnd) {
    // Use the nested struct within the Player scope
    std::vector<Player::PlayableOption> playableTiles;
    std::vector<std::string> tiles = hand.getHandTiles();

    // Check if the computer (Index 1) passed to unlock the right side
    const int COMPUTER_INDEX = 1;
    bool oppPassed = gameRound.isPassed(COMPUTER_INDEX);

    //left and right version of the same tile will be added if both can be added
    for (int i = 0; i < (int)tiles.size(); i++) {
        std::pair<int, int> p = parseTile(tiles[i]);
        bool isDouble = (p.first == p.second);

        bool matchesLeft = (p.first == leftEnd || p.second == leftEnd);
        bool matchesRight = (p.first == rightEnd || p.second == rightEnd);

        // Evaluate Left side playability
        if (matchesLeft) {
            playableTiles.push_back({ i, 'L' });
        }

        // Evaluate Right side playability (Opponent's side)
        if (matchesRight && (isDouble || oppPassed)) {
            playableTiles.push_back({ i, 'R' });
        }
       
    }
    return playableTiles;
}


int Human::getValidatedInt(int min, int max)
{
    int value;

    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        cin >> value;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }

        if (value < min || value > max)
        {
            cout << "Please enter a number between "
                << min << " and " << max << endl;
            continue;
        }

        return value;
    }
}


char Human::getValidatedSide()
{
    char side;

    //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (true)
    {
        cout << "Side L or R (only choose right if opponent passed): ";
        cin >> side;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input!" << endl;
            continue;
        }

        side = toupper(side);

        if (side == 'L' || side == 'R')
            return side;

        cout << "Invalid side selection." << endl;
    }
}

std::string Human::getValidatedTileFromHand()
{
    std::vector<std::string> tiles = hand.getHandTiles();
    std::string chosen;

    while (true)
    {
        cout << "Enter the tile you want to place: ";
        std::getline(cin, chosen);

        if (std::find(tiles.begin(), tiles.end(), chosen) != tiles.end())
            return chosen;

        cout << chosen << " isn't in your hand." << endl;
    }
}

bool Human::matchesLeft(const std::pair<int, int>& pips,
    int leftEnd) const
{
    return (pips.first == leftEnd || pips.second == leftEnd);
}

bool Human::matchesRight(const std::pair<int, int>& pips,int rightEnd) const
{
    return (pips.first == rightEnd ||
        pips.second == rightEnd);
}


bool Human::canPlayRight(const std::pair<int, int>& pips,
    int rightEnd,
    Round& gameRound) const
{
    const int COMPUTER_INDEX = 1;

    bool oppPassed = gameRound.isPassed(COMPUTER_INDEX);
    
    bool isDouble = (pips.first == pips.second);
    
    

    if (!matchesRight(pips, rightEnd))
    {
        cout << "Tile doesn't match right pip. " << endl;
    }

    if (!oppPassed && !isDouble)
    {
        cout << "Opponent has not passed yet and tile isn't double. " << endl;
    }

    return matchesRight(pips, rightEnd) &&
        (isDouble || oppPassed);
}

void Human::handleDraw(Player::Move& move,
    Stock& gameStock,
    Round& gameRound,
    int leftEnd,
    int rightEnd)
{
    std::string drawnTile = gameStock.drawTile();
    hand.addTile(drawnTile);

    cout << returnID()
        << " drew "
        << drawnTile
        << endl;

    std::pair<int, int> pips = parseTile(drawnTile);

    //check
    bool canLeft = matchesLeft(pips, leftEnd);
    bool canRight = canPlayRight(pips, rightEnd, gameRound);

    move.draw = true;

    // If playable on both sides
    if (canLeft && canRight)
    {
        move.side = getValidatedSide();
        move.chosenTile = drawnTile;
    }
    else if (canLeft)
    {
        move.side = 'L';
        move.chosenTile = drawnTile;
    }
    else if (canRight)
    {
        move.side = 'R';
        move.chosenTile = drawnTile;
    }
    else
    {
        cout << "Can't play "
            << drawnTile
            << " anywhere."
            << endl;

        move.draw = false;
        move.passed = true;
    }
}

/* *********************************************************************
Function Name: takeTurn
Purpose: To facilitate the human player's turn via console input and validation.
Parameters:
   gameStock, a Stock object passed by value. Contains the boneyard.
   gameRound, a Round object passed by reference. Maintains round state.
   leftEnd, integer value of the left layout end.
   rightEnd, integer value of the right layout end.
Return Value: A Move structure containing the player's validated choice.
Algorithm:
   1) Determine if the player has any legal moves.
   2) Enter a loop to prompt the user for an action (Play, Draw, Pass, Help).
   3) If playing: validate the chosen index and ensure the move matches the chosen side's pips.
   4) If drawing: ensure the boneyard is not empty.
   5) If passing: ensure the boneyard is empty and no playable tiles exist.
   6) Return the finalized move details.
Reference: Input validation structure assisted by Gemini AI.
********************************************************************* */
Player::Move Human::takeTurn(Stock& gameStock,
    Round gameRound,
    int leftEnd,
    int rightEnd)
{
    Player::Move move;

    // Initialize defaults
    move.draw = false;
    move.passed = false;
    move.help = false;
    move.chosenTile = "";
    move.side = ' ';
    move.hasPlayableTiles = false;

    // Check for playable tiles
    vector<PlayableOption> playableList =
        findPlayableTiles(hand, gameRound, leftEnd, rightEnd);

    if (!playableList.empty())
        move.hasPlayableTiles = true;

    bool choiceValid = false;

    const short ONE = 1;
    const short TWO = 2;
    const short THREE = 3;
    const short FOUR = 4;
    while (!choiceValid)
    {
        
        cout << "1=Play 2=Draw 3=Pass 4=Help ";
        int choice = getValidatedInt(ONE, FOUR);

        // =========================================
        // PLAY
        // =========================================
        if (choice == ONE)
        {
            //extract leftover input characters that won't interfear with the next input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            move.chosenTile = getValidatedTileFromHand();

            pair<int, int> pips = parseTile(move.chosenTile);

            move.side = getValidatedSide();

            if (move.side == 'L')
            {
                if (matchesLeft(pips, leftEnd))
                {
                    choiceValid = true;
                }
                else
                {
                    cout << "Invalid Left move. Tile doesn't match."
                        << endl;
                }
            }
            else if (move.side == 'R')
            {
                if (canPlayRight(pips, rightEnd, gameRound))
                {
                    choiceValid = true;
                }
                else
                {
                    cout << "Invalid Right move." << endl;
                }
            }
        }

        // =========================================
        // DRAW
        // =========================================
        else if (choice == TWO)
        {
            if (gameStock.getBoneyard().empty())
            {
                cout << "Sorry. You can't draw since the boneyard is empty."
                    << endl;
                continue;
            }

            if (move.hasPlayableTiles)
            {
                cout << "Sorry. You still have tiles you can play."
                    << endl;
                continue;
            } 

            handleDraw(move,
                gameStock,
                gameRound,
                leftEnd,
                rightEnd);

            choiceValid = true;
        }

        // =========================================
        // PASS
        // =========================================
        else if (choice == THREE)
        {
            bool drawPass = move.draw && !move.hasPlayableTiles;
            bool normalPass =
                gameStock.getBoneyard().empty() &&
                !move.hasPlayableTiles;
            
            /*
            if (drawPass || normalPass)
            {
                move.passed = true;
                choiceValid = true;
            }
            else
            {
                if (move.hasPlayableTiles)
                {
                    cout << "Sorry, you still have tiles you can play."
                        << endl;
                }
                else
                {
                    cout << "To pass you must either:" << endl;
                    cout << "A) Draw a tile and be unable to play it, or"
                        << endl;
                    cout << "B) Have no playable tiles AND an empty boneyard."
                        << endl;
                }
            }  */

            //debug code
            move.passed = true;
            choiceValid = true;

        }

        // =========================================
        // HELP
        // =========================================
        else if (choice == FOUR)
        {
            Computer helper;
            helper.help(this,
                move,
                gameStock,
                gameRound,
                leftEnd,
                rightEnd);

            // allow player to choose again
            choiceValid = false;
        }
    }

    return move;
}