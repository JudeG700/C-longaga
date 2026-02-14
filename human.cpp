#include "human.h"
#include <iostream>
#include "Computer.h"
#include "round.h"

using namespace std;
/* *********************************************************************
Function Name: Human (Constructors)
Purpose: To initialize the Human player object, either as a default
         instance or with a specific starting hand.
Parameters:
            hand, a Hand object. Passed by value.
Return Value: None.
Algorithm:
            1) Assign the provided hand to the internal member variable.
            2) Initialize player-specific identifiers.
Reference: None.
********************************************************************* */
Human::Human() {}
Human::Human(Hand hand) { this->hand = hand; }


std::pair<int, int> Human::parseTile(const std::string& tile) {
    size_t dash = tile.find('-');
    if (dash == std::string::npos) return { -1, -1 }; // Safety return

    int left = std::stoi(tile.substr(0, dash));
    int right = std::stoi(tile.substr(dash + 1));
    return { left, right };
}


/* *********************************************************************
Function Name: returnID
Purpose: To identify the player as a human for display and logic purposes.
Parameters: None.
Return Value: A string containing "Human".
Reference: None.
********************************************************************* */

std::vector<int> Human::findPlayableTiles(Hand& playerHand, Round& gameRound, int leftEnd, int rightEnd)
{

    std::vector<int> playable;
    std::vector<std::string> tiles = playerHand.getHandTiles();   // works ONLY if getHand returns reference

    bool oppPassed = gameRound.isPassed(1);

    for (int i = 0; i < (int)tiles.size(); i++)
    {
        std::pair<int, int> p = parseTile(tiles[i]);
        int a = p.first;
        int b = p.second;
        bool isDouble = (a == b);

        bool canPlayLeft = (a == leftEnd || b == leftEnd);

        // Right side is only valid if (Matches Right) AND (is Double OR Opponent Passed)
        bool canPlayRight = (a == rightEnd || b == rightEnd) && (isDouble || oppPassed);

        if (canPlayLeft || canPlayRight || isDouble)
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

std::string Human::returnID() const
{
    return ID;
}

/* *********************************************************************
Function Name: takeTurn
Purpose: To manage the user interface for a human player's turn,
         collecting and validating their choice of action.
Parameters:
            gameStock, a Stock object. Passed by value.
            leftEnd, an integer representing the leftmost board value.
            rightEnd, an integer representing the rightmost board value.
Return Value: A Move structure containing the validated player action.
Algorithm:
            1) Prompt the user to choose between playing a tile, drawing,
               passing, or requesting help.
            2) If playing, prompt for a tile index and validate that it
               exists within the player's current hand.
            3) Prompt for the board side (Left or Right) and validate the input.
            4) If drawing, verify that tiles remain in the boneyard before
               setting the draw status.
            5) If help is requested, utilize the computer's heuristic logic
               to suggest an optimal move.
            6) Package the validated selections into a Move object and return it.
Reference: Logic for input validation loops assisted by AI.
********************************************************************* */
Move Human::takeTurn(Stock gameStock, Round gameRound, int leftEnd, int rightEnd)  // declared here
{
    Move move;

    move.draw = false;
    move.passed = false;
    move.help = false;
    move.tileIndex = -1;
    move.side = ' ';
    move.hasPlayableTiles = false;

    vector<int> tiles = findPlayableTiles(hand, gameRound, leftEnd, rightEnd);
    //if there are playable tiles
    if (!tiles.empty())
    {
        move.hasPlayableTiles = true;
    }
    
    bool choiceValid = 0;
    while (!choiceValid)
    {
        int choice = -1;
        do {
            cout << "1=Play 2=Draw 3=Pass 4=Help ";
            cin >> choice;
        } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);

        if (choice == 1) {
            move.draw = false;
            move.passed = false;

            do {
                cout << "Tile index (0-" << hand.getHandTiles().size() - 1 << "): ";
                cin >> move.tileIndex;
            } while (move.tileIndex < 0 || move.tileIndex >= hand.getHandTiles().size());

            do {
                cout << "Side L or R (only choose right if opponent passed): ";
                cin >> move.side;
            } while (move.side != 'L' && move.side != 'R');

            string tile = hand.getHandTiles()[move.tileIndex];
            pair<int, int> p = parseTile(tile); // Use your parse utility
            int a = p.first;
            int b = p.second;
            bool isDouble = (a == b);

            
            if (move.side == 'L') {
                if (a == leftEnd || b == leftEnd || isDouble) {
                    choiceValid = true; // SUCCESS
                }
                else {
                    cout << "Invalid Left move. Tile doesn't match." << endl;
                }
            }
            else if (move.side == 'R') {
                bool oppPassed = gameRound.isPassed(1);
                if (isDouble || oppPassed) {
                    if (a == rightEnd || b == rightEnd || isDouble) {
                        choiceValid = true; // SUCCESS
                    }
                    else {
                        cout << "Invalid Right move. Tile doesn't match." << endl;
                    }
                }
                else {
                    cout << "Sorry. You can't move Right unless opponent passed or it's a double." << endl;
                }
            }
        }
        else if (choice == 2) {
            // Draw logic
            if (gameStock.getBoneyard().empty()) {
                cout << "Boneyard empty!" << endl;
            }
            else {
                move.draw = true;
                choiceValid = true;
            }
        }
        else if (choice == 3) {
            
            if (!gameStock.getBoneyard().empty() || move.hasPlayableTiles)
            {
                cout << "Sorry. Can't pass unless boneyard is empty and you have no playable tiles left" << endl;
                choiceValid = false;

            }
            else
            {
                move.passed = true;
                choiceValid = true;
            }
            
        }
        else if (choice == 4)
        {
            move.help = true;
            move.draw = false;
            move.passed = false;
            move.hasPlayableTiles = false;
        }
    }
    
    return move;
}