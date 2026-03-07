/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <Windows.h>
#include "layout.h"
#include "layoutView.h"
#include "stock.h"
#include "hand.h"
#include "round.h"
#include "player.h"
#include "human.h"
#include "computer.h"
#include "tournament.h"

using namespace std;

/* *********************************************************************
Function Name: Round (Constructor)
Purpose: To initialize a new round object with default game state values.
Parameters: None.
Return Value: None.
Algorithm:
   1) Initialize round number to 1 and engine index to 0.
   2) Set default engine tiles to "6-6".
   3) Populate the list of rotating required engines from 6-6 to 0-0.
   4) Reset all player pass statuses to false.
Reference: re-modeled all functions and constructors with help of Gemini.
********************************************************************* */

Round::Round() :
	roundNum(1),
	engineIndex(0),
	currentPlayer(0),
	nextPlayer(0),
	roundOverFlag(true)
{
	requiredEngines = { "6-6", "5-5", "4-4", "3-3", "2-2", "1-1", "0-0" };
	passed.fill(false);
}


Round::Round(Player* p[])
{

	players[0] = p[0];
	players[1] = p[1];
	roundNum = 1;
	engineIndex = 0;
	currentPlayer = 0;
	nextPlayer = 0;
	roundOverFlag = true;
	requiredEngines = { "6-6", "5-5", "4-4", "3-3", "2-2", "1-1", "0-0" };
	passed.fill(false);

}

/* *********************************************************************
Function Name: isRoundOver
Purpose: To check if the current round has concluded.
Parameters: None.
Return Value: Boolean; true if the round is over.
Reference: None.
********************************************************************* */
bool Round::isRoundOver() const {
    return roundOverFlag;
}

/* *********************************************************************
Function Name: roundOver
Purpose: To signal that the current round has ended.
Parameters: None.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::roundOver() {
    roundOverFlag = true;
}

/* *********************************************************************
Function Name: nextRound
Purpose: To advance the game state to the next round.
Parameters: None.
Return Value: None.
Algorithm:
   1) Set roundOverFlag to false to allow new play.
   2) Increment the round count.
   3) Reset passes for all players.
Reference: None.
********************************************************************* */
void Round::nextRound() {
    roundOverFlag = false;
    roundNum++;
    resetPasses();
}

/* *********************************************************************
Function Name: setRoundNum
Purpose: To manually set the current round number.
Parameters:
   roundNumber, an integer representing the new round count.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setRoundNum(int roundNumber) {
    this->roundNum = roundNumber;
}

/* *********************************************************************
Function Name: getRoundNum
Purpose: To retrieve the current round number.
Parameters: None.
Return Value: Integer representing the round count.
Reference: None.
********************************************************************* */
int Round::getRoundNum() const {
    return roundNum;
}

/* *********************************************************************
Function Name: incEIndex
Purpose: To increment the index used to track which double is required.
Parameters: None.
Return Value: None.
Algorithm:
   1) Increment the index by one.
   2) Use modulo operation with the size of requiredEngines to wrap around.
Reference: Built by me but static_cast added by gemini
********************************************************************* */
void Round::incEIndex() {
    engineIndex = (engineIndex + 1) % static_cast<int>(requiredEngines.size());
}


/* *********************************************************************
Function Name: getEngine
Purpose: To retrieve the engine tile currently on the board.
Parameters: None.
Return Value: String representation of the engine tile.
Reference: None.
********************************************************************* */
string Round::getEngine() const {
    return engine;
} 

/* *********************************************************************
Function Name: getRequiredEngine
Purpose: To retrieve the tile required to start the current round.
Parameters: None.
Return Value: String representing the required double.
Reference: None.
********************************************************************* */
string Round::getRequiredEngine() const {
    return requiredEngine;
}

/* *********************************************************************
Function Name: determineEngine
Purpose: To check if a specific hand contains the required engine tile.
Parameters:
   playerHand, a vector of strings passed by reference.
Return Value: The matching tile string, or an empty string if not found.
Algorithm:
   1) Iterate through the player's tiles.
   2) Compare each tile to the requiredEngine value.
   3) Return the tile if a match is found.
Reference: Assistance from chatgpt.
********************************************************************* */
string Round::determineEngine(const vector<string>& playerHand) {

    //find the required engine within the player's hand
    for (const auto& tile : playerHand) {
        if (tile == requiredEngine) {
            engine = tile;
            return engine;
        }
    }
    
    return "";
}

/* *********************************************************************
Function Name: determineRequiredEngine
Purpose: To calculate which engine is required based on the round number.
Parameters: None.
Return Value: None.
Algorithm:
   1) Calculate the index using (roundNum - 1) % 7.
   2) Set the requiredEngine from the pre-defined list.
Reference: None.
********************************************************************* */
void Round::determineRequiredEngine() {
    //engine will decrement every round from 6-6 to 5-5 before going back to 6-6 
    int index = (roundNum - 1) % requiredEngines.size();
    requiredEngine = requiredEngines[index];
}

/* *********************************************************************
Function Name: setCurrentPlayer
Purpose: To update the index of the player whose turn it is.
Parameters:
   playerIndex, an integer (0 for Human, 1 for Computer).
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setCurrentPlayer(int playerIndex) {
    this->currentPlayer = playerIndex;
}

/* *********************************************************************
Function Name: setNextPlayer
Purpose: To update the index of the player who will move next.
Parameters:
   playerIndex, an integer.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setNextPlayer(int playerIndex) {
    this->nextPlayer = playerIndex;
}

/* *********************************************************************
Function Name: getCurrentPlayer
Purpose: To retrieve the index of the current active player.
Parameters: None.
Return Value: Integer player index.
Reference: None.
********************************************************************* */
int Round::getCurrentPlayer() const {
    return currentPlayer;
}

/* *********************************************************************
Function Name: getNextPlayer
Purpose: To retrieve the index of the player next in turn.
Parameters: None.
Return Value: Integer player index.
Reference: None.
********************************************************************* */
int Round::getNextPlayer() const {
    return nextPlayer;
}

/* *********************************************************************
Function Name: resetPasses
Purpose: To clear the pass status for all players at the start of a turn cycle.
Parameters: None.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::resetPasses() {
    passed[0] = false;
    passed[1] = false;
}

/* *********************************************************************
Function Name: setPassed
Purpose: To record that a specific player has passed their turn.
Parameters:
   playerIndex, an integer representing the player.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::setPassed(int playerIndex) {
    passed[playerIndex] = true;
}

/* *********************************************************************
Function Name: resetPass
Purpose: To clear the pass status for a specific player after they move.
Parameters:
   playerIndex, an integer representing the player.
Return Value: None.
Reference: None.
********************************************************************* */
void Round::resetPass(int playerIndex) {
    passed[playerIndex] = false;
}

/* *********************************************************************
Function Name: bothPassed
Purpose: To check if both players have passed consecutively.
Parameters: None.
Return Value: Boolean; true if both pass flags are set.
Reference: None.
********************************************************************* */
bool Round::bothPassed() const {
    return passed[0] && passed[1];
}

/* *********************************************************************
Function Name: isPassed
Purpose: To check if a specific player is currently in a passed state.
Parameters:
   playerIndex, an integer.
Return Value: Boolean pass status.
Reference: None.
********************************************************************* */
bool Round::isPassed(int playerIndex) const {
    return passed[playerIndex];
}

/* *********************************************************************
Function Name: yesNo
Purpose: Converts a boolean state to a printable "Yes" or "No" string.
Parameters:
   stateValue, a boolean value.
Return Value: A string.
Reference: Assistance from chatgpt.
********************************************************************* */
string Round::yesNo(bool stateValue) const {
    return stateValue ? "Yes" : "No";
}

/* *********************************************************************
Function Name: checkWinner
Purpose: To determine if either player has won the round by emptying their hand.
Parameters:
   humanPlayer, a Player object pointer. Passed by value.
   computerPlayer, a Player object pointer. Passed by value.
Return Value: A pointer to the winning Player, or nullptr if none.
Algorithm:
   1) Access the human player's hand tiles; if empty, human wins.
   2) Access the computer player's hand tiles; if empty, computer wins.
   3) Otherwise, return nullptr.
Reference: Assistance from chatgpt.
********************************************************************* */
Player* Round::checkWinner(Player* humanPlayer, Player* computerPlayer) {
    // Access hand tiles via the hand object
    if (humanPlayer->getHand().getHandTiles().empty()) {
        cout << "Human wins the round" << endl;
        return humanPlayer;
    }
    if (computerPlayer->getHand().getHandTiles().empty()) {
        cout << "Computer wins the round" << endl;
        return computerPlayer;
    }
    return nullptr;
}



int Round::menu()
{
	int option = 0;
	cout << "Longaga" << endl;
	do
	{
		cout << "Select an option " << endl;

		cout << "1. New game" << endl;
		cout << "2. Load game" << endl;
		cin >> option;

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
	} while (option < 1 || option > 2);

	return option;
}

/* *********************************************************************
Function Name: showLoadMenu
Purpose: Scans the local directory for saved text files and allows the
		 user to select one to load.
Parameters: none
Return Value: string, the filename of the selected save file.
Algorithm:
			1) Use the Windows API (FindFirstFileA) to look for all
			   files ending in ".txt".
			2) Store all matching filenames in a vector and display them
			   with an index number to the user.
			3) Prompt the user to enter the number corresponding to their
			   desired save file.
			4) Validate the number against the vector size.
			5) Return the string filename at the selected index.
Reference: Windows API file searching logic adapted from MSDN documentation and assistance from google Gemini
********************************************************************* */
string Round::showLoadMenu() {
	std::vector<std::string> saveFiles;
	WIN32_FIND_DATAA findFileData; // Added 'A' here

	// Using the 'A' version to avoid Unicode errors
	HANDLE hFind = FindFirstFileA("*.txt", &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::cout << "No save files found." << std::endl;
		return " ";
	}

	//pull saved files
	std::cout << "--- AVAILABLE SAVES ---" << std::endl;
	int count = 1;

	do {
		std::string filename = findFileData.cFileName;
		saveFiles.push_back(filename);
		std::cout << count << ") " << filename << std::endl;
		count++;
	} while (FindNextFileA(hFind, &findFileData) != 0);


	FindClose(hFind);

	int choice = -1;

	do
	{
		std::cout << "Select a file number to load: ";
		std::cin >> choice;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid input!" << endl;
			continue;
		}
	} while (choice < 0 && choice >(int)saveFiles.size());

	string fileName = "";

	std::string selectedFile = saveFiles[choice - 1];
	std::cout << "Loading: " << selectedFile << "..." << std::endl;
	fileName = selectedFile;
	cout << endl;


	return fileName;
}
/* *********************************************************************
Function Name: checkHandForTile
Purpose: Determines if a specific tile (or its flipped equivalent)
		 exists within a player's hand.
Parameters:
			p: Pointer to the Player object. Passed by reference (pointer).
			   Not modified.
			target: The tile string (e.g., "6-6") to find. Passed by value.
Return Value: bool, true if the tile is found in the hand, false otherwise.
Algorithm:
			1) Validate that the player pointer is not null.
			2) Retrieve the list of tiles currently in the player's hand.
			3) Create a "flipped" string of the target (e.g., "1-2" becomes "2-1").
			4) Iterate through the hand vector.
			5) Return true if the current tile matches the target or the
			   flipped target; otherwise, return false after the loop.
Reference: none
********************************************************************* */

bool Round::checkHandForTile(Player* p, string target) {
	if (p == nullptr)
	{
		return false;
	}

	// Get the hand from the player
	vector<string> handTiles = p->getHandTiles();

	// Create the flipped version of the tile (e.g., "1-2" becomes "2-1")
	string flipped = "";
	if (target.length() >= 3) {
		flipped += target[2];
		flipped += '-';
		flipped += target[0];
	}

	// Loop through the hand to see if either version exists
	for (const string& tile : handTiles) {
		if (tile == target || tile == flipped) {
			return true;
		}
	}
	return false;
}



/* *********************************************************************
Function Name: applyMove
Purpose: Validates and executes a tile placement, draw, or pass action.
Parameters:
			player, a pointer to the current Player object.
			layout, the Layout object passed by reference.
			gamestock, the Stock object passed by reference.
			move, a Move structure containing the turn details.
Return Value: bool, true if the move was valid and executed, false otherwise.
Algorithm:
			1) Check if the move is a help request, draw, or pass.
			2) If a tile is played, validate the tile index and matching ends.
			3) If necessary, flip the tile string to match the layout end.
			4) Add the tile to the layout deque and remove it from the player's hand.
Reference: Logic for flipping tiles assisted by Gemini.
********************************************************************* */
bool Round::applyMove(
	Player* player,
	Player::Move move
) {



	//if they decide to pass, the next player takes their turn
	if (move.passed) {

		cout << player->returnID() << " passed" << endl;
		return true;
	}


	const vector<string>& tiles = player->getHandTiles();

	//coonvert selected tile to ints for both sides

	//get the left end of the tile
	int a = move.chosenTile[0] - '0';


	//get the right end of the tile
	int b = move.chosenTile[2] - '0';

	//get left and right end
	int leftEnd = layout.returnLeft();
	int rightEnd = layout.returnRight();

	//if it is placed
	bool placed = false;

	//double tile
	bool isDouble = (a == b);

	//if the player chose to play their tile on the left side
	if (move.side == 'L') {

		//if tile is a double
		if (isDouble)
		{
			layout.addLeft(move.chosenTile);
		}
		//if right side matches left side of layout
		else if (b == leftEnd)
		{
			layout.addLeft(move.chosenTile);

		}
		//if the left side matches the left side of the layout, we flip
		else if (a == leftEnd) {
			string flipped = ""; flipped += move.chosenTile[2]; flipped += '-'; flipped += move.chosenTile[0];
			cout << player->returnID() << " flipped " << move.chosenTile << " left to " << flipped << endl;
			layout.addLeft(flipped);
		}

		if (player->returnID() == "Human")
		{
			cout << player->returnID() << " played " << move.chosenTile << " on left side of layout " << endl;
		}


	}
	//if the player chose to play their tile on the right side
	else if (move.side == 'R') {

		//if tile is a double
		if (isDouble)
		{
			layout.addRight(move.chosenTile);
		}
		//if left side matches right side of layout
		else if (a == rightEnd)
		{
			layout.addRight(move.chosenTile);

		}
		//if the right side matches the right side of the layout, we flip
		else if (b == rightEnd) {
			string flipped = ""; flipped += move.chosenTile[2]; flipped += '-'; flipped += move.chosenTile[0];
			cout << player->returnID() << " flipped " << move.chosenTile << " right to " << flipped << endl;

			layout.addRight(flipped);
		}
		if (player->returnID() == "Human")
		{
			cout << player->returnID() << " played " << move.chosenTile << " on right side of layout " << endl;
		}

	}


	//SECTION BUILT USING GEMINI 

	//this is just used to document the moves that the computer makes
	if (player->returnID() == "Computer")
	{
		//the name of the side to be picked
		string sideName;

		// the proximity of the computer
		string referencePoint = "";

		if (player->returnID() == "Computer")
		{
			// the name of the side to be picked
			sideName = (move.side == 'L') ? "left" : "right";

			cout << "GAMEROUND ENGINE: " << endl;
			cout << getEngine() << endl;

			if (sideName == "left")
			{
				if (layout.returnLeftTile() == getEngine())
				{
					referencePoint = "engine";
				}
				else
				{
					referencePoint = "layout";
				}
			}
			else if (sideName == "right")
			{
				if (layout.returnRightTile() == getEngine())
				{
					referencePoint = "engine";
				}
				else
				{
					referencePoint = "layout";
				}
			}
		}

		if (move.passed) {
			cout << player->returnID() << " passed." << endl;
		}
		else {
			cout << "The " << player->returnID() << " placed " << move.chosenTile
				<< " to the " << sideName << " of the " << referencePoint << "." << endl;

			if (move.chosenTile[0] == move.chosenTile[2])
			{
				cout << "Trying to get rid of doubles as soon as possible" << endl;
				cout << "Doubles placed left on player's side for purpose of messing their tile streak up" << endl;
			}
			else
			{
				int totalPipValue = a + b;
				cout << "The pips on my current tile, " << move.chosenTile[0] << " and " << move.chosenTile[2] << ", add up to " << totalPipValue << ", which is a higher sum value than the other tiles I can play" << endl;
				cout << "Continuing to hold tiles with lots of pips would soften the blow if I were to lose; the player gets less points" << endl;
			}
		}
	}

	cout << endl;

	//Remove the tile from the player's hand after it has been deposited
	int tileIndex = player->getIndexByTile(move.chosenTile);

	//since the tile is set, this would realistically never happen
	if (tileIndex != -1)
	{
		player->removeTile(tileIndex);
	}
	return true;
}




/* *********************************************************************
Function Name: addTotalPoints / tiePoints
Purpose: Calculates and updates tournament scores at the end of a round.
Parameters:
			winner and loser, Player objects passed by reference.
Return Value: none
Algorithm:
			1) Sum the pips (numeric values) of every tile remaining in the loser's hand.
			2) Add that total sum to the winner's tournament score.
Reference: Calculation logic assisted by ChatGPT.
********************************************************************* */
void Round::addTotalPoints(Player& winner, Player& loser, Tournament& gameTournament) {
	int total = 0;

	// sum the pips in loser hand
	const vector<string> loserHand = loser.getHand().getHandTiles();

	//convert left and right end to ints to add up total pips on each side
	for (const auto& tile : loserHand) {
		int a = tile[0] - '0';
		int b = tile[2] - '0';
		total += a + b;
	}

	//if human wins the round
	if (winner.returnID() == "Human")
	{
		std::cout << "Human wins the round! +" << total << " points\n";
		gameTournament.addPlayerScore(total);
	}
	//if computer wins the round
	else if (winner.returnID() == "Computer")
	{
		std::cout << "Computer wins the round! +" << total << " points\n";
		gameTournament.addComputerScore(total);
	}


}


/* *********************************************************************
Function Name: tiePoints
Purpose: Determines the winner of a blocked round by comparing the total
		 pip counts of both players' hands.
Parameters:
			Human: Pointer to the Human player object. Passed by reference.
			Computer: Pointer to the Computer player object. Passed by reference.
			gameTournament: The Tournament object. Passed by reference.
				Modified by adding the loser's pips to the winner's score.
Return Value: none
Algorithm:
			1) Calculate the sum of all pips in the Human's hand.
			2) Calculate the sum of all pips in the Computer's hand.
			3) Compare the two sums; the player with the lower sum wins.
			4) Add the points from the loser's hand (or the opponent's
			   total) to the winner's tournament score.
			5) Print the result of the tie-breaker to the console.
Reference: none
********************************************************************* */
void Round::tiePoints(Player* Human, Player* Computer)
{
	//sum of points for human
	//add pips from each tile
	int sumHuman = 0;
	for (const auto& tile : Human->getHandTiles()) {
		int a = tile[0] - '0';
		int b = tile[2] - '0';
		sumHuman += a + b;
	}

	//sum of points for computer
	//add pips from each tile
	int sumComputer = 0;
	for (const auto& tile : Computer->getHandTiles()) {
		int a = tile[0] - '0';
		int b = tile[2] - '0';
		sumComputer += a + b;
	}

	//if human player's total pips are greater than computer's
	if (sumHuman < sumComputer) {
		gameTournament.addPlayerScore(sumComputer);
		std::cout << "Computer wins the tied round! +" << sumComputer << " points\n";
	}
	//if computer player's total pips are greater than human's
	else if (sumComputer < sumHuman) {
		gameTournament.addComputerScore(sumHuman);
		std::cout << "Human wins the tied round! +" << sumHuman << " points\n";
	}
	else {
		std::cout << "Tied round is a draw. No points awarded.\n";
	}



}

/* *********************************************************************
Function Name: obtainEngine
Purpose: Automates the process of finding the "Engine" (the starting tile)
		 at the beginning of a round.
Parameters:
			gameRound: The Round object. Passed by value.
			players: An array of Player pointers. Passed by reference.
			gameStock: The Stock object (boneyard). Passed by reference.
Return Value: string, the tile that will serve as the engine.
Algorithm:
			1) Determine which engine is required for the current round
			   (e.g., 6-6 for Round 1, 5-5 for Round 2).
			2) Check the Human's hand for the engine.
			3) If not found, check the Computer's hand.
			4) If neither player has the engine, enter a loop where both
			   players draw tiles from the boneyard one by one.
			5) Terminate the loop as soon as a player draws the required engine.
			6) Return the engine string.
Reference: none
********************************************************************* */
string Round::obtainEngine()
{
	string engine = "";

	//see what the engine should be based on round(6-6 for round 1, 5-5 for round 2)
	determineRequiredEngine();

	//we can find the engine now that we know which one we need
	engine = determineEngine(players[0]->getHandTiles());
	if (engine == "")
	{
		//if human doesn't have the engine, they look in computer's tile
		cout << "Human doesn't have the engine " << endl;
		engine = determineEngine(players[1]->getHandTiles());

		//if computer has the engine
		if (engine != "")
		{
			cout << "Computer has the engine" << endl;
			cout << "Computer takes first turn" << endl;

		}
		//if computer doesn't have the engine
		else
		{
			cout << "Computer doesn't have engine either" << endl;
			cout << "Proceeding with drawing... " << endl;
			cout << endl;

		}

	}
	else
	{
		cout << "Human has engine" << endl;
		cout << "Human takes first turn" << endl;
	}



	//if no player has the engine, they will both keep drawing tiles until they receive one
	//The player that receives the engine first will go first
	while (engine == "") {

		string humanDraw, compDraw;
		// Human tries to retrieve engine
		humanDraw = gameStock.drawTile();   // Stock gives a tile
		players[0]->addTile(humanDraw);              // Add to human hand
		cout << "Human draws: " << humanDraw << endl;

		if (humanDraw == getRequiredEngine()) {
			engine = humanDraw;
			cout << "Human obtained engine!" << endl;
			cout << "Human goes first!" << endl;

			break;
		}

		// Computer tries to retrieve engine
		compDraw = gameStock.drawTile();          // Stock gives a tile
		players[1]->addTile(compDraw);           // Add to computer hand
		cout << "Computer draws: " << compDraw << endl;


		if (compDraw == getRequiredEngine()) {
			engine = compDraw;
			cout << "Computer obtained engine!" << endl;
			cout << "Computer goes first!" << endl;
			break;


		}
	}


	return engine;

}


/* *********************************************************************
Function Name: firstTurn
Purpose: Handles the initial state transition of a round by placing the
		 engine on the board and determining the turn order.
Parameters:
			engine: The tile string required to start the round. Passed by value.
			layout: The Layout object. Passed by reference. Modified by
				adding the engine as the first element.
			players: Array of Player pointers. Passed by reference.
				Modified by removing the engine from the owner's hand.
			gameRound: The Round object. Passed by reference.
				Modified to set the starting player for the round.
Return Value: none
Algorithm:
			1) Add the engine tile to the layout.
			2) Search both players' hands to identify who possessed the engine.
			3) Set the starting player to the opponent of the engine owner.
			4) Remove the engine tile from the owner's hand to ensure
			   the hand size reflects the play.
Reference: none
********************************************************************* */
void Round::firstTurn(string engine)
{
	//play tile
	layout.addLeft(engine);


	//placedTile[gameRound.getCurrentPlayer()] = 1;

	//whoever has the engine takes the first turn

	int engineOwner = -1;
	if (players[0]->hasTile(engine)) {
		engineOwner = 0; // Human
		setCurrentPlayer(1); // Set next turn to Computer
	}
	else {
		engineOwner = 1; // Computer
		setCurrentPlayer(0); // Set next turn to Human
	}


	//remove whatever tile is in player's hand
	vector<string> hand = players[engineOwner]->getHandTiles();
	for (int i = 0; i < hand.size(); i++) {
		// Check both orientations just in case
		string flipped = ""; flipped += engine[2]; flipped += '-'; flipped += engine[0];
		if (hand[i] == engine || hand[i] == flipped) {
			//play tile
			players[engineOwner]->removeTile(i);
			break;
		}
	}

}


void Round::setupNewGame()
{
	layout.clearChain();
	gameStock.shuffle();

	//deal tiles to each player's hands
	players[0]->setTiles(gameStock.deal());
	players[1]->setTiles(gameStock.deal());

}

void Round::showBoard(Tournament gameTournament)
{
	LayoutView gameView;

	cout << "_______________________________________" << endl;
	cout << "Round no.: " << getRoundNum() << endl;
	cout << endl;

	cout << "Computer: " << endl;
	cout << "	";
	players[1]->getHand().displayHand();
	cout << endl;
	cout << "	" << "Score: " << gameTournament.getComputerScore() << endl;
	cout << endl;

	cout << "Human: " << endl;
	cout << "	";
	players[0]->getHand().displayHand();
	cout << endl;
	cout << "	" << "Score: " << gameTournament.getPlayerScore() << endl;
	cout << endl;

	cout << "Layout: " << endl;
	cout << "	";
	gameView.display(layout.getChain());
	cout << endl;

	cout << "Boneyard: " << endl;
	gameStock.display();
	cout << "_______________________________________" << endl;
	cout << endl;
}

void Round::play(Player* players[2])
{
	int non_draw_passes = 0;
	string engine = "";

	cout << "SS: " << isRoundOver() << endl;
	if (layout.isEmpty() && isRoundOver())
	{
		engine = obtainEngine();
		firstTurn(engine);
	}



    while (!roundEnded)
    {
        Player::Move move;


		//make move
        move = players[currentPlayer]->takeTurn(gameStock, *this, layout.returnLeft(), layout.returnRight());
        applyMove(players[currentPlayer], move);

		//check to see if round ended
        if (players[0]->getHandTiles().empty() || players[1]->getHandTiles().empty())
        {
			roundEnded = true;
        }

		const short MAX_CONSEC_PASSES = 2;

		//if a player chose to pass
		if (move.passed)
		{
			//they are now set to passed
			setPassed(getCurrentPlayer());

			//the boneyard being empty wouldn't matter as there would have to be
			if (!move.draw && gameStock.getBoneyard().empty())
			{
				non_draw_passes++;

			}
			

			//if both players simultaneously passed
			if (non_draw_passes == MAX_CONSEC_PASSES)
			{
				cout << "Both players have passed. It's a tie" << endl;
				roundOver();

				//break;
			}

		}
		else
		{
			//reset consecutive passes
			non_draw_passes = 0;

			//if the player passed on their previous turn
			if (isPassed(getCurrentPlayer()))
			{
				//un-set their pass status
				//cout << "CUR: " << gameRound.getCurrentPlayer() << endl;
				resetPass(getCurrentPlayer());
			}
		}


		//initSave();

		//polymorphic loop
        currentPlayer = 1 - currentPlayer;
    }

}

bool Round::initialize(Tournament& gameTournament)
{
	//used to determine if it is a new round
	bool roundInitialized = false;



	bool isValidChoice = 0;
	while (!isValidChoice)
	{
		//Sent to menu first
		int option = menu();


		//if starting a new game
		if (option == 1)
		{
			int tournamentScore = 0;
			const short MIN_TOURN_SCORE = 50;
			const short MAX_TOURN_SCORE = 250;

			do
			{
				cout << "Enter the tournament score (between 50 & 250): " << endl;
				cin >> tournamentScore;

				//made with google gemini
				if (cin.fail()) {


					cin.clear();
					cin.ignore(1000, '\n');
					cout << "Invalid input!" << endl;
					continue;
				}

			} while (tournamentScore < MIN_TOURN_SCORE || tournamentScore > MAX_TOURN_SCORE);

			isValidChoice = true;

			//set the required score for the tournament
			gameTournament.setTournScore(tournamentScore);
		}
		else if (option == 2)
		{

			//the name for the file
			string loadName = "";
			loadName = showLoadMenu();

			if (loadName != " ")
			{
				cout << "resuming loaded game " << endl;
				roundInitialized = gameTournament.loadGameState(loadName, players[0], players[1], gameStock, gameTournament, layout, *this);
				isValidChoice = true;
			}

		}
	}
	return roundInitialized;

}