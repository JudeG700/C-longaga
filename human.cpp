/************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS - 366 OPL
* Date : 2 / 13 / 2026
* ***********************************************************
*/

#include "human.h"
#include <iostream>
#include "Computer.h"
#include "round.h"

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
Move Human::takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd) {
    Move move;

    // Initialize move defaults
    move.draw = false;
    move.passed = false;
    move.help = false;
    move.tileIndex = -1;
    move.side = ' ';
    move.hasPlayableTiles = false;

    // Check hand for any legal moves
    vector<PlayableOption> playableList = findPlayableTiles(hand, gameRound, leftEnd, rightEnd);
    if (!playableList.empty()) {
        move.hasPlayableTiles = true;
    }

    //to check if the selected move is valid
    bool choiceValid = false;

    while (!choiceValid) {
        int choice = -1;

        // Main menu loop
        do {
            cout << "1=Play 2=Draw 3=Pass 4=Help ";
            cin >> choice;

            //made with google gemini
            if (cin.fail()) {
                // 1. Clear the error flag
                cin.clear();

                // 2. Ignore everything in the buffer until the next newline
                // This "throws away" the bad characters (like the 'a')
                cin.ignore(1000, '\n');

                cout << "Invalid input!" << endl;
                continue; // Restart the loop
            }
        } while (choice < 1 || choice > 4);

        //if they chose to place a tile
        if (choice == 1) {
            // Handle tile index selection
            do {
                cout << "Tile index (0-" << hand.getHandTiles().size() - 1 << "): ";
                cin >> move.tileIndex;

                //made with google gemini
                if (cin.fail()) {
                    // 1. Clear the error flag
                    cin.clear();

                    // 2. Ignore everything in the buffer until the next newline
                    // This "throws away" the bad characters (like the 'a')
                    cin.ignore(1000, '\n');

                    cout << "Invalid input!" << endl;
                    continue; // Restart the loop
                }
            } while (move.tileIndex < 0 || move.tileIndex >= (int)hand.getHandTiles().size());

            //Handle side selection
            do {
                cout << "Side L or R (only choose right if opponent passed): ";
                cin >> move.side;

                //made with google gemini
                if (cin.fail()) {
                    // 1. Clear the error flag
                    cin.clear();

                    // 2. Ignore everything in the buffer until the next newline
                    // This "throws away" the bad characters (like the 'a')
                    cin.ignore(1000, '\n');

                    cout << "Invalid input!" << endl;
                    continue; // Restart the loop
                }

                move.side = toupper(move.side);


            } while (move.side != 'L' && move.side != 'R');

            string tile = hand.getHandTiles()[move.tileIndex];
            pair<int, int> pips = parseTile(tile);
            bool isDouble = (pips.first == pips.second);

            if (move.side == 'L') {
                // Verify left side match or double rule
                if (pips.first == leftEnd || pips.second == leftEnd || isDouble) {
                    choiceValid = true;
                }
                else {
                    cout << "Invalid Left move. Tile doesn't match." << endl;
                }
            }
            else if (move.side == 'R') {
                // Verify right side match (requires double or opponent pass)
                const int COMPUTER_PLAYER_INDEX = 1;
                bool oppPassed = gameRound.isPassed(COMPUTER_PLAYER_INDEX);

                //if opponent passed or tile is a double
                if (isDouble || oppPassed) {
                    if (pips.first == rightEnd || pips.second == rightEnd) {
                        choiceValid = true;
                    }
                    else {
                        cout << "Invalid Right move. Tile doesn't match." << endl;
                    }
                }
                else {
                    cout << "You can't place tiles on your opponent's side unless they've passed." << endl;
                }
            }
        }
        //if they draw
        else if (choice == 2) {
            // Verify boneyard availability before drawing
            if (gameStock.getBoneyard().empty()) {
                cout << "Boneyard empty!" << endl;
            }
            else {
                move.draw = true;
                choiceValid = true;
            }
        }
        //if they pass
        else if (choice == 3) {
            // Verify pass conditions: empty boneyard AND no playable moves
            if (!gameStock.getBoneyard().empty() || move.hasPlayableTiles) {
                cout << "Sorry. You can't pass unless the boneyard is empty and you have no playable tiles." << endl;
            }
            else {
                move.passed = true;
                choiceValid = true;
            }
        }
        //if they request help
        else if (choice == 4) {
            // Set help flag for external hint logic
            move.help = true;
            choiceValid = true;
        }

        
    }
    return move;
}