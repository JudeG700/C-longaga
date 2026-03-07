/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

#include "tournament.h"
#include "round.h"
#include <iostream>
#include <string>

Tournament::Tournament(Player* p[2])
{
	players[0] = p[0];
	players[1] = p[1];
	humanScore = 0;
	computerScore = 0;
	targetScore = 0;
}
/* *********************************************************************
Function Name: addPlayerScore
Purpose: To update the human player's cumulative tournament total.
Parameters:
            points, an integer. The sum of pips from the opponent's hand.
            Passed by value.
Return Value: None.
Algorithm:
            1) Receive the calculated point value from the completed round.
            2) Add this value to the human player's total tournament score.
Reference: None.
********************************************************************* */
void Tournament::addPlayerScore(int points)
{
    humanScore += points;
}

/* *********************************************************************
Function Name: addComputerScore
Purpose: To update the computer player's cumulative tournament total.
Parameters:
            points, an integer. The sum of pips from the opponent's hand.
            Passed by value.
Return Value: None.
Algorithm:
            1) Receive the calculated point value from the completed round.
            2) Add this value to the computer player's total tournament score.
Reference: None.
********************************************************************* */
void Tournament::addComputerScore(int points)
{
    computerScore += points;
}

void Tournament::addScore(int points, Player* player)
{
	if (player->returnID() == "Human")
	{
		humanScore += points;
	}
	else if(player->returnID() == "Computer")
	{
		computerScore += points;
	}
}

/* *********************************************************************
Function Name: getPlayerScore
Purpose: To retrieve the human player's current total points.
Parameters: None.
Return Value: Integer, the current score.
Reference: None.
********************************************************************* */
int Tournament::getPlayerScore() const
{
    return humanScore;
}

/* *********************************************************************
Function Name: getComputerScore
Purpose: To retrieve the computer player's current total points.
Parameters: None.
Return Value: Integer, the current score.
Reference: None.
********************************************************************* */
int Tournament::getComputerScore() const
{
    return computerScore;
}

/* *********************************************************************
Function Name: getTournScore
Purpose: To retrieve the target score required to win the tournament.
Parameters: None.
Return Value: Integer, the winning threshold.
Reference: None.
********************************************************************* */
int Tournament::getTournScore() const
{
    return targetScore;
}

void Tournament::setTournScore(int targetScore)
{
    this->targetScore = targetScore;
}
/* *********************************************************************
Function Name: determineWinner
Purpose: To evaluate if the tournament has concluded and identify the victor.
Parameters: None.
Return Value: A string containing the name of the winner ("Human" or "Computer"),
              or an empty string if the tournament is still in progress.
Algorithm:
            1) Check if either player has reached or exceeded the target score.
            2) If the threshold is met, compare the human and computer scores.
            3) Identify the player with the higher total as the winner.
            4) Return the result or signal that the tournament continues.
Reference: chatgpt helped with implementing this
********************************************************************* */
std::string Tournament::determineWinner()
{
    //if the human player's score or the computer player's score is greater than the target score?
    if (humanScore >= targetScore || computerScore >= targetScore)
    {
        return (humanScore > computerScore) ? "Human" : "Computer";
    }
    return ""; 
}

/* *********************************************************************
Function Name: setComputerScore
Purpose: To update the cumulative tournament score for the computer player.
Parameters:
   newScore, an integer representing the updated score value.
Return Value: None.
Algorithm:
   1) Assign the value of newScore to the member variable computerScore.
Reference: None.
********************************************************************* */
void Tournament::setComputerScore(int newScore) {
    computerScore = newScore;
}

/* *********************************************************************
Function Name: setHumanScore
Purpose: To update the cumulative tournament score for the human player.
Parameters:
   newScore, an integer representing the updated score value.
Return Value: None.
Algorithm:
   1) Assign the value of newScore to the member variable humanScore.
Reference: None.
********************************************************************* */
void Tournament::setHumanScore(int newScore) {
    humanScore = newScore;
}

void Tournament::play()
{
    while (humanScore != 200 || computerScore != 200)
    {
		Round currentRound(players);

		if (!currentRound.initialize(*this))
		{
			currentRound.setupNewGame();
		}

		currentRound.play(players);
		

		if (currentRound.bothPassed())
		{
			currentRound.tiePoints(players[0], players[1]);
		}
		else
		{
			Player* winner = currentRound.checkWinner(players[0], players[1]);

			if (winner != nullptr)
			{
				Player* loser;

				cout << "winner: " << winner->returnID() << endl;

				if (winner->returnID() == "Human")
				{
					loser = players[1];
				}
				else
				{
					loser = players[0];
				}

				//give the winning player their score
				calculatePoints(*winner, *loser);

			}
		}
		
		//make the engine be the next engine
		//gameRound.incEIndex();

		//increment round number
		//gameRound.nextRound();

		//the required engine is the engine lower than the preceeding one
		//gameRound.setRequiredEngine();
		//gameRound.determineRequiredEngine();

		//clear chain
		//layout.clearChain();

		//reset the game stock
		//gameStock.reset();

		//empty both hands
		//players[0]->emptyHand();
		//players[1]->emptyHand();

		//reset
		//roundInitialized = false;


		cout << endl;

		cout << "The round has ended " << endl;
		Sleep(2000);

		cout << "Points for each player so far: " << endl;
		cout << "__________________________________________" << endl;
		cout << "Human: " << getPlayerScore() << endl;
		cout << "Computer: " << getComputerScore() << endl;
		cout << "__________________________________________" << endl;
		Sleep(2000);
		//the round class will call the tournament class to update scores
	 
        //addScore();
    }
}


/* *********************************************************************
Function Name: saveGameState
Purpose: Serializes the current game state into a JSON file using the Cereal library.
Parameters:
			playerHand, computerHand, gameStock, tournament, layout, currentRound.
			All passed by reference.
Return Value: none
Algorithm:
			1) Open an output file stream "gamestate.json".
			2) Initialize a Cereal JSONOutputArchive.
			3) Map each game object (hands, boneyard, layout, etc.) to a named JSON key.
			4) Close the archive and file stream.
			5) Terminate the program with exit(0) to fulfill "Save and Quit" requirement.
Reference: Google gemini
********************************************************************* */
void Tournament::saveGameState(string filename, Player* human, Player* computer, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound) {

	std::ofstream outFile(filename);

	if (!outFile)
	{
		return;
	}

	//using \n for speedier writing
	outFile << "Tournament Score: " << tournament.getTournScore() << "\n";
	outFile << "Round No.: " << currentRound.getRoundNum() << "\n\n";

	outFile << "Computer:\n";
	outFile << "   Hand: ";
	for (auto const& tile : computer->getHand().getHandTiles()) outFile << tile << " ";
	outFile << "\n   Score: " << tournament.getComputerScore() << "\n\n";

	outFile << "Human:\n";
	outFile << "   Hand: ";
	for (auto const& tile : human->getHand().getHandTiles()) outFile << tile << " ";
	outFile << "\n   Score: " << tournament.getPlayerScore() << "\n\n";

	outFile << "Layout:\n";
	outFile << "  L ";
	for (auto const& tile : layout.getChain()) outFile << tile << " ";
	outFile << "R\n\n";

	outFile << "Boneyard:\n";
	for (auto const& tile : gameStock.getBoneyard()) outFile << tile << " ";
	outFile << "\n\n";

	cout << "current player: " << currentRound.getCurrentPlayer() << endl;
	cout << "did they pass?: " << currentRound.isPassed(currentRound.getCurrentPlayer()) << endl;
	outFile << "Previous Player Passed: " << (currentRound.isPassed(currentRound.getCurrentPlayer()) ? "Yes" : "No") << "\n\n";
	//outFile << "Previous Player Passed: " << (currentRound.isPassed(currentRound.getNextPlayer()) ? "Yes" : "No") << "\n\n";

	// Assuming 0 is Human and 1 is Computer
	outFile << "Next Player: " << (currentRound.getNextPlayer() == 1 ? "Computer" : "Human") << "\n";
	cout << "next player: " << currentRound.getNextPlayer() << endl;

	cout << "Game saved to " << filename << endl;

	outFile.close();

	exit(0);
}


/* *********************************************************************
Function Name: loadGameState
Purpose: To restore the game to a specific previous state by parsing a
		 text-based save file. This allows players to resume a match
		 exactly where they left off.
Parameters:
			filename, a string containing the path to the file. Passed by value.
			playerHand, the Hand object for the human. Passed by reference.
				Modified by clearing existing tiles and populating them
				with tiles found in the file.
			computerHand, the Hand object for the computer. Passed by reference.
				Modified by populating it with tiles found in the file.
			gameStock, the Stock object (Boneyard). Passed by reference.
				Modified to reflect the remaining tiles listed in the file.
			tournament, the Tournament object. Passed by reference.
				Modified to restore the overall scores.
			layout, the Layout object. Passed by reference.
				Modified to rebuild the sequence of tiles currently on the board.
			currentRound, the Round object. Passed by reference.
				Modified to set round number, next player, and pass status.
Return Value: none
Algorithm:
			1) Open the specified file stream; if unsuccessful, exit function.
			2) Read the file line-by-line using a loop.
			3) Use string searching (find) to identify keywords like "Human:",
			   "Layout:", or "Next Player:".
			4) Extract the substring data following the identified keywords.
			5) For tile collections, use a stringstream to parse space-separated
			   strings into individual tile data.
			6) Update the corresponding game objects using setter methods.
			7) Close the file stream.
Reference: Logic for string parsing and stringstream usage assisted by Gemini.
********************************************************************* */
bool Tournament::loadGameState(string filename, Player* human, Player* computer, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound) {


	bool isInitialized = 1;

	bool passVal = 0;

	ifstream is(filename);
	if (!is) return false;

	string line;
	while (getline(is, line)) {
		// 1. Tournament Score
		if (line.find("Tournament Score:") != string::npos) {
			size_t colonPos = line.find(":");
			if (colonPos != string::npos) {
				string value = line.substr(colonPos + 1);
				setTournScore(stoi(value));
			}
			//should be error without tournament score

			//			tournament.setTournScore(std::stoi(line.substr(line.find(":") + 1)));
		}
		// 2. Round Number
		else if (line.find("Round No.:") != std::string::npos) {
			size_t colonPos = line.find(":");
			if (colonPos != string::npos) {
				string value = line.substr(colonPos + 1); //+1 to find data item after it
				//if can't find value should throw error
				currentRound.setRoundNum(stoi(value));
			}

			//currentRound.setRoundNum(std::stoi(line.substr(line.find(":") + 1)));
		}
		// 3. Computer player's hand
		else if (line.find("Computer:") != string::npos) {
			if (getline(is, line) && line.find("Hand:") != string::npos) {

				size_t colonPos = line.find(":");
				if (colonPos != string::npos) {
					string tilesStr = line.substr(colonPos + 1);

					stringstream ss(tilesStr);
					string tempTile;
					vector<string> loadedTiles;

					while (ss >> tempTile)
						loadedTiles.push_back(tempTile);

					//even if they have no tiles, it's still acceptable
					computer->setTiles(loadedTiles);
				}
			}


			if (getline(is, line) && line.find("Score:") != string::npos) {

				size_t colonPos = line.find(":");
				if (colonPos != std::string::npos) {
					std::string value = line.substr(colonPos + 1);
					setComputerScore(std::stoi(value));
				}
			}


		}
		// 4. Human Hand
		else if (line.find("Human:") != std::string::npos) {


			if (std::getline(is, line) && line.find("Hand:") != std::string::npos) {

				size_t colonPos = line.find(":");
				if (colonPos != std::string::npos) {

					std::string tilesStr = line.substr(colonPos + 1);

					std::stringstream ss(tilesStr);
					std::string tempTile;
					std::vector<std::string> loadedTiles;

					while (ss >> tempTile)
						loadedTiles.push_back(tempTile);

					human->setTiles(loadedTiles);
				}
			}

			if (getline(is, line) && line.find("Score:") != string::npos) {

				size_t colonPos = line.find(":");
				if (colonPos != std::string::npos) {
					std::string value = line.substr(colonPos + 1);
					setHumanScore(std::stoi(value));
				}
			}

		}
		//load game layout
		else if (line.find("Layout:") != string::npos)
		{

			if (getline(is, line) && line.find("L") != string::npos) {
				// Find the text between L and R
				size_t start = line.find("L") + 1;
				//size_t start = line.find("L");
				size_t end = line.find("R");
				if (start < end && end != string::npos) {
					string tilesStr = line.substr(start, end - start);
					//parse
					stringstream ss(tilesStr);
					string temp;

					//add
					while (ss >> temp)
					{
						layout.addRight(temp);
					}
				}
			}


		}
		//if boneyard keyword is found
		else if (line.find("Boneyard:") != string::npos)
		{
			vector<string> boneyardTiles;
			//we will enter and see what is there
			if (std::getline(is, line) && !line.empty()) {
				// If there's no colon on this line, don't use find(":")!
				stringstream ss(line);
				string t;
				while (ss >> t) boneyardTiles.push_back(t);
				gameStock.setBoneyard(boneyardTiles);
			}
			//set to empty if uninitialized
			else
			{
				gameStock.setBoneyard(boneyardTiles);
			}
		}
		//load previous player that passed
		else if (line.find("Previous Player Passed:") != std::string::npos) {
			string val = line.substr(line.find(":") + 2); // Get "Yes" or "No"
			//for the current player
			if (val == "Yes")
			{
				passVal = 1;
			}
			else if (val == "No")
			{
				passVal = 0;
			}
			//currentRound.setPassed(val == "Yes");
		}
		//load the next player
		else if (line.find("Next Player:") != std::string::npos) {
			//string nextName = line.substr(line.find(":") + 2); 
			size_t colonPos = line.find(":");
			if (colonPos != std::string::npos) {

				std::string nextName = line.substr(colonPos + 1);


				if (nextName.find("Computer") != std::string::npos)
				{
					//set current player to computer
					currentRound.setCurrentPlayer(1);
					currentRound.setNextPlayer(0);
				}
				else if (nextName.find("Human") != std::string::npos)
				{
					//set current player to human
					currentRound.setCurrentPlayer(0);
					currentRound.setNextPlayer(1);
				}

				//In the previous save, the next player is the current player now
				//likewise, the one that went before is also the next player as well
				if (!passVal)
				{
					currentRound.resetPass(currentRound.getNextPlayer());
				}
				else
				{
					currentRound.setPassed(currentRound.getNextPlayer());
				}
			}

		}




	}
	is.close();

	//we start a new round here
	//if the layout is empty but boneyard isn't we assume a round as started, and we go find the engine
	//if the boneyard is empty but layout isn't, we assume that we are in the middle of a round where the boneyard is empty
	if (gameStock.getBoneyard().empty() && layout.isEmpty())
	{
		isInitialized = false;
	}


	return isInitialized;
}


/**
 * @brief Prompt-driven wrapper for saveGameState.
 * Allows the user to save and exit the application safely after each player takes a turn and after a round is over
 */
void Tournament::initSave(Player* Human, Player* Computer, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound)
{
	int inp;
	do
	{
		cout << "Would you like to save?" << endl;
		cout << "1. Yes " << endl;
		cout << "2. No " << endl;
		cout << "Note: Saving here will exit the game " << endl;
		cin >> inp;

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

	} while (inp < 1 || inp > 2);


	if (inp == 1)
	{
		string fileName;
		int fileSize = fileName.size();
		bool isValidFileName = 0;

		do
		{
			cout << "Enter name for save file (e.g., game1.txt): ";
			cin >> fileName;

			if (fileName.length() >= 4 &&
				fileName.substr(fileName.length() - 4) == ".txt") {
				isValidFileName = true;
			}
			else {
				cout << "Error: File must end in .txt" << endl;
			}
		} while (!isValidFileName);
		saveGameState(fileName, players[0], players[1], gameStock, tournament, layout, currentRound);
	}
	else
	{
		return;
	}
}
