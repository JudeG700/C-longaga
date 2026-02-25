/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

// c++ longaga.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


/*
-hasPassed not working
-draw feature not working either
-really understand all longaga rules
*/

#include "header.h"
/* *********************************************************************
Function Name: menu
Purpose: Displays the game's entry point and validates the user's choice
		 between starting fresh or resuming a previous session.
Parameters: none
Return Value: int, representing the user's validated choice (1 or 2).
Algorithm:
			1) Print the game title "Longaga" and the two primary options.
			2) Capture user input from the console.
			3) Use a do-while loop to repeat the prompt if the input is
			   not 1 or 2.
			4) Return the valid integer to the main control flow.
Reference: none
********************************************************************* */
int menu()
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
string showLoadMenu() {
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
	} while (choice < 0 && choice > (int)saveFiles.size());
	
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
bool checkHandForTile(Player* p, string target) {
	if (p == nullptr) return false;

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
void saveGameState(string filename, Hand humanHand, Hand computerHand, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound) {

	std::ofstream outFile(filename);

	if (!outFile) return;

	outFile << "Tournament Score: " << tournament.getTournScore() << "\n";
	outFile << "Round No.: " << currentRound.getRoundNum() << "\n\n";

	outFile << "Computer:\n";
	outFile << "   Hand: ";
	for (auto const& tile : computerHand.getHandTiles()) outFile << tile << " ";
	outFile << "\n   Score: " << tournament.getComputerScore() << "\n\n";

	outFile << "Human:\n";
	outFile << "   Hand: ";
	for (auto const& tile : humanHand.getHandTiles()) outFile << tile << " ";
	outFile << "\n   Score: " << tournament.getPlayerScore() << "\n\n";

	outFile << "Layout:\n";
	outFile << "  L ";
	for (auto const& tile : layout.getChain()) outFile << tile << " ";
	outFile << "R\n\n";

	outFile << "Boneyard:\n";
	for (auto const& tile : gameStock.getBoneyard()) outFile << tile << " ";
	outFile << "\n\n";

	cout << "PPPPPPPPPPPPPPPPPPPPPP: " << currentRound.getCurrentPlayer() << endl;
	cout << "OOOOOOOOOOOOOOOOOOOOOO: " << currentRound.isPassed(currentRound.getCurrentPlayer()) << endl;
	outFile << "Previous Player Passed: " << (currentRound.isPassed(currentRound.getCurrentPlayer()) ? "Yes" : "No") << "\n\n";

	// Assuming 0 is Human and 1 is Computer
	outFile << "Next Player: " << (currentRound.getNextPlayer() == 1 ? "Computer" : "Human") << "\n";
	cout << "NNNNNNNNNNNNNNNNNNNNNN: " << currentRound.getCurrentPlayer() << endl;

	cout << "Game saved to " << filename << endl;
	gameStock.reset();

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
void loadGameState (string filename, Player* human, Player* computer, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound) {
	
	bool passVal = 0;

	ifstream is(filename);
	if (!is) return;

	string line;
	while (getline(is, line)) {
		// 1. Tournament Score
		if (line.find("Tournament Score:") != string::npos) {
			size_t colonPos = line.find(":");
			if (colonPos != string::npos) {
				string value = line.substr(colonPos + 1);
				tournament.setTournScore(stoi(value));
			}
			//			tournament.setTournScore(std::stoi(line.substr(line.find(":") + 1)));
		}
		// 2. Round Number
		else if (line.find("Round No.:") != std::string::npos) {
			size_t colonPos = line.find(":");
			if (colonPos != string::npos) {
				string value = line.substr(colonPos + 1);
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

					computer->setTiles(loadedTiles);
				}
			}

			if (getline(is, line) && line.find("Score:") != string::npos) {

				size_t colonPos = line.find(":");
				if (colonPos != std::string::npos) {
					std::string value = line.substr(colonPos + 1);
					tournament.setComputerScore(std::stoi(value));
				}
			}
			

		}
		// 4. Human Hand
		else if (line.find("Human:") != std::string::npos) {

			/*
			std::getline(is, line); // Move to "Hand:" line
			std::string tilesStr = line.substr(line.find(":") + 2);

			stringstream ss(tilesStr);
			string tempTile;
			vector<string> loadedTiles;

			while (ss >> tempTile) { 
				loadedTiles.push_back(tempTile);
			}

			//set the human player's score
			humanHand.setTiles(loadedTiles);

			std::getline(is, line);
			if (line.find("Score:"))
			{
				int scoreVal = std::stoi(line.substr(line.find(":") + 2));
				tournament.setHumanScore(scoreVal);
			}
			// Same logic for humanHand
			*/


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
					tournament.setHumanScore(std::stoi(value));
				}
			}

		} 
		//load game layout
		else if (line.find("Layout:") != string::npos)
		{

			if (getline(is, line) && line.find("L") != string::npos) {
				// Find the text between L and R
				size_t start = line.find("L") + 2;
				//size_t start = line.find("L");
				size_t end = line.find("R");
				if (start < end && end != string::npos) {
					string tilesStr = line.substr(start, end - start);
					stringstream ss(tilesStr);
					string temp;
					while (ss >> temp) layout.addRight(temp);
				}
			}

		
		}
		//load boneyard
		else if (line.find("Boneyard:") != string::npos)
		{
			if (std::getline(is, line) && !line.empty()) {
				// If there's no colon on this line, don't use find(":")!
				stringstream ss(line);
				string t;
				vector<string> boneyardTiles;
				while (ss >> t) boneyardTiles.push_back(t);
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
			else if(val == "No")
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
					currentRound.setCurrentPlayer(1);
					currentRound.setNextPlayer(0);
				}
				else if (nextName.find("Human") != std::string::npos)
				{
					currentRound.setCurrentPlayer(0);
					currentRound.setNextPlayer(1);
				}

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
}


/**
 * @brief Prompt-driven wrapper for saveGameState.
 * Allows the user to save and exit the application safely after each player takes a turn and after a round is over
 */
void initSave(Hand humanHand, Hand computerHand, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound)
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
		saveGameState(fileName, humanHand, computerHand, gameStock, tournament, layout, currentRound);
	}
	else
	{
		return;
	}
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
bool applyMove(
	Player* player,
	Layout& layout,
	Stock& gamestock,
	Round& gameRound,
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

	//if player chose to play left side
	if (move.side == 'L') {

		
		if (isDouble)
		{
			layout.addLeft(move.chosenTile);
		}
		//if b matches
		else if (b == leftEnd) 
		{
			layout.addLeft(move.chosenTile);

		}
		//if side a matches we flip
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
	else if (move.side == 'R') {

		if (isDouble)
		{
			layout.addRight(move.chosenTile);
		}
		else if (a == rightEnd)
		{
			layout.addRight(move.chosenTile);

		}
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
		
		string sideName = (move.side == 'L') ? "left" : "right";

		string referencePoint = (layout.getChain().size() <= 2) ? "engine" : "layout";
		
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
		Sleep(1000);
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
void addTotalPoints(Player& winner, Player& loser, Tournament& gameTournament) {
	int total = 0;

	// sum the pips in loser hand
	const vector<string> loserHand = loser.getHand().getHandTiles();

	//convert left and right end to ints to add up total pips on each side
	for (const auto& tile : loserHand) {
		int a = tile[0] - '0';
		int b = tile[2] - '0';
		total += a + b;
	}

	if (winner.returnID() == "Human")
	{
		std::cout << "Human wins the round! +" << total << " points\n";
		gameTournament.addPlayerScore(total);
	}
	else if(winner.returnID() == "Computer")
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
void tiePoints(Player* Human, Player* Computer, Tournament& gameTournament)
{

	int sumHuman = 0;
	for (const auto& tile : Human->getHandTiles()) {
		int a = tile[0] - '0';
		int b = tile[2] - '0';
		sumHuman += a + b;
	}

	int sumComputer = 0;
	for (const auto& tile : Computer->getHandTiles()) {
		int a = tile[0] - '0';
		int b = tile[2] - '0';
		sumComputer += a + b;
	}

	if (sumHuman < sumComputer) {
		gameTournament.addPlayerScore(sumComputer);
		std::cout << "Human wins the tied round! +" << sumComputer << " points\n";
	}
	else if (sumComputer < sumHuman) {
		gameTournament.addComputerScore(sumHuman);
		std::cout << "Computer wins the tied round! +" << sumHuman << " points\n";
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
string obtainEngine(Round gameRound, Player* players[], Stock& gameStock)
{
	string engine = "";
	gameRound.determineRequiredEngine();

	engine = gameRound.determineEngine(players[0]->getHandTiles());
	if (engine == "")
	{
		cout << "Human doesn't have the engine " << endl;
		engine = gameRound.determineEngine(players[1]->getHandTiles());


		if (engine != "")
		{
			cout << "Computer has the engine" << endl;
			cout << "Computer takes first turn" << endl;

		}
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

		if (humanDraw == gameRound.getRequiredEngine()) {
			engine = humanDraw;
			cout << "Human obtained engine!" << endl;
			cout << "Human goes first!" << endl;

			break;
		}

		// Computer tries to retrieve engine
		compDraw = gameStock.drawTile();          // Stock gives a tile
		players[1]->addTile(compDraw);           // Add to computer hand
		cout << "Computer draws: " << compDraw << endl;


		if (compDraw == gameRound.getRequiredEngine()) {
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
void firstTurn(string engine, Layout& layout, Player* players[], Round& gameRound)
{

	layout.addLeft(engine);
	int engineOwner = -1;
	if (checkHandForTile(players[0], engine)) {
		engineOwner = 0; // Human
		gameRound.setCurrentPlayer(1); // Set next turn to Computer
	}
	else {
		engineOwner = 1; // Computer
		gameRound.setCurrentPlayer(0); // Set next turn to Human
	}

	// 3. NOW REMOVE it from the owner's hand
	vector<string> hand = players[engineOwner]->getHandTiles();
	for (int i = 0; i < hand.size(); i++) {
		// Check both orientations just in case
		string flipped = ""; flipped += engine[2]; flipped += '-'; flipped += engine[0];
		if (hand[i] == engine || hand[i] == flipped) {
			players[engineOwner]->removeTile(i);
			break;
		}
	}

}

int main()
{
	
	//move object used for documenting moves
	Player::Move move;



	//hands
	Hand humanHand;
	Hand computerHand;

	//players
	Human human(humanHand);
	Computer computer(computerHand);

	//polymorphism for players
	Player* players[2];
	players[0] = &human;
	players[1] = &computer;

	//layout
	Layout layout;


	//ends of the layout
	int leftEnd;
	int rightEnd;

	//rounds
	Round gameRound;

	//stocks
	Stock gameStock;

	//to view the layout while playing
	LayoutView gameView;

	//Tournament
	Tournament gameTournament;


	bool roundInitialized = false;

	//Sent to menu first
	int option = menu();

	//if starting a new game
	if (option == 1)
	{
		int tournamentScore = 0;
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

		} while (tournamentScore < 50 || tournamentScore > 250);

		
		//set the required score for the tournament
		gameTournament.setTournScore(tournamentScore);
		roundInitialized = false; //why here???
	}
	else if (option == 2)
	{
		cout << "resuming loaded game " << endl;
		string loadName = "";
		if ((loadName = showLoadMenu()) == " ")
		{
			menu();
		}
		loadGameState(loadName, players[0], players[1], gameStock, gameTournament, layout, gameRound);
		roundInitialized = true;

	}
	//Continues looping until the tournament score is reached
	while (gameTournament.getPlayerScore() < gameTournament.getTournScore() && gameTournament.getComputerScore() < gameTournament.getTournScore())
	{

		//if this hasn't come from a player loading a game
		string engine = "";

		if (!roundInitialized)
		{
			layout.clearChain();
			gameStock.reset();        // however you reset stock
			gameStock.shuffle();

			//deal tiles to each player's hands
			players[0]->setTiles(gameStock.deal());
			players[1]->setTiles(gameStock.deal());


			//obtain engine

		}


		if (layout.isEmpty() && !gameRound.isRoundOver())
		{
			engine = obtainEngine(gameRound, players, gameStock);
			firstTurn(engine, layout, players, gameRound);
		}

		//whoever has the engine first takes the first turn

		roundInitialized = true;


		cout << endl;
		cout << "Get ready for round " << gameRound.getRoundNum() << endl;
		Sleep(2000);


		//------------------------------
		//store data in variables to save them
		//humanHand = players[0]->getHand();
		//computerHand = players[1]->getHand();

		//if a round was won
		/*if (gameWon)
		{
				
			//saves it too a copy
			initSave(humanHand, computerHand, gameStock, gameTournament, layout, gameRound);
		} */
		//------------------------------
	

		//determine if player placed a tile
		bool placedTile[2] = { false, false };


		//while current round isn't over
		while (!gameRound.isRoundOver())
		{

			//get layout ends AFTER obtaining the engine
			leftEnd = layout.returnLeft();
			rightEnd = layout.returnRight();


			//current and next player's index (0 and 1)
			int currIdx = gameRound.getCurrentPlayer();
			int nextIdx = 1 - currIdx;
			
			//set next player
			gameRound.setNextPlayer(nextIdx);

			//UI layout
			cout << "_______________________________________" << endl;
			cout << "Tournament Score: " << gameTournament.getTournScore() << endl;
			cout << "Round no.: " << gameRound.getRoundNum() << endl;
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

			//if both players take their turn, ensure to offer human player to save
			if (placedTile[0] == 1 && placedTile[1] == 1)
			{
				humanHand = players[0]->getHand();
				computerHand = players[1]->getHand();
				cout << endl;
				cout << "_______________________________________" << endl;
				initSave(players[0]->getHand(), players[1]->getHand(), gameStock, gameTournament, layout, gameRound);
				placedTile[0] = 0;
				placedTile[1] = 0;
			} 

			
			cout << "Previous Player Passed: " << gameRound.yesNo(gameRound.isPassed(gameRound.getNextPlayer())) << endl;
			cout << endl;
			/*
			cout << "Next Player: " << players[nextIdx]->returnID() << endl;
			*/


			

			//to ensure move function returns true
			bool moveWasSuccessful = 0;

			//move object to store move details from move.h
			Player::Move move;


			//do
			//{
				
			//IMPLEMENTED BUG CHECK WITH CHATGPT
			//error checking for players
			if (players[0] == nullptr || players[1] == nullptr) {
				cout << "Memory Error: Players not initialized!" << endl;
				return 1;
			}

			if (gameRound.getCurrentPlayer() < 0 || gameRound.getCurrentPlayer() > 1) {
				cout << "Memory Error: currentPlayer index out of bounds: " << gameRound.getCurrentPlayer() << endl;
				return 1;
			}

			//get the move
			move = players[gameRound.getCurrentPlayer()]->takeTurn(gameStock, gameRound, leftEnd, rightEnd);
				

			//apply the move to the layout
			moveWasSuccessful = applyMove(players[gameRound.getCurrentPlayer()], layout, gameStock, gameRound, move);
				

			//update the ends
//			leftEnd = layout.returnLeft();
//			rightEnd = layout.returnRight();

			vector<string>boneyard = gameStock.getBoneyard();

			//if a player chose to pass
			if (move.passed)
			{
				//they are now set to passed
				gameRound.setPassed(gameRound.getCurrentPlayer());


				//if the opponent pass right before the player did, and the boneyard is empty, it's a tie
				if (gameRound.bothPassed() && boneyard.empty()) //FIX!!!!!!!!
				{
					cout << "Both players have passed. It's a tie" << endl;
					gameRound.roundOver();
					moveWasSuccessful = true;

					break;
				}
					
			}
			else 
			{
				//if the player passed on their previous turn
				if (gameRound.isPassed(gameRound.getCurrentPlayer()))
				{
					//un-set their pass status
					cout << "CUR: " << gameRound.getCurrentPlayer() << endl;
					gameRound.resetPass(gameRound.getCurrentPlayer());
				}
			}

				
				

			//} while (!moveWasSuccessful);

			//give time to process computer opponent's move (the only two players are human and computer)
			if (gameRound.getCurrentPlayer() == 1)
			{
				Sleep(1000);
			}


			//player placed a tile
			placedTile[gameRound.getCurrentPlayer()] = 1;

			//if either hand is empty, the round ends and the winner is determined
			if (players[0]->getHandTiles().empty() || players[1]->getHandTiles().empty())
			{
				gameRound.roundOver();
			}
			
			
			//let next player take their turn
			gameRound.setCurrentPlayer(nextIdx);

		} 



		//if there is a set winner
		if (!gameRound.bothPassed())
		{
			//check which one emptied their hand
			Player* winner = gameRound.checkWinner(players[0], players[1]);

			
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
				addTotalPoints(*winner, *loser, gameTournament);

			}
				//help from chatgpt when running bug check

		}
		//if nobody won and it's a tie
		else if(gameRound.bothPassed())
		{
			//whoever has the least tiles wins the round
			tiePoints(players[0], players[1], gameTournament);

			//reset passes for next round
			gameRound.resetPasses();


		}
		
		//make the engine be the next engine
		gameRound.incEIndex();

		//increment round number
		gameRound.nextRound();

		//the required engine is the engine lower than the preceeding one
		//gameRound.setRequiredEngine();
		gameRound.determineRequiredEngine();

		//clear chain
		layout.clearChain();

		//reset the game stock
		gameStock.reset();

		//empty both hands
		players[0]->emptyHand();
		players[1]->emptyHand();

		//reset
		roundInitialized = false;


		cout << endl;

		cout << "The round has ended " << endl;
		Sleep(2000);

		cout << "Points for each player so far: " << endl;
		cout << "__________________________________________" << endl;
		cout << "Human: " << gameTournament.getPlayerScore() << endl;
		cout << "Computer: " << gameTournament.getComputerScore() << endl;
		cout << "__________________________________________" << endl;
		Sleep(2000);
		


		//offer player to save when round ends
		//gameWon = 1;
	}


	string winner = gameTournament.determineWinner();
	cout << endl;
	cout << "The tournament is over because the tournament score has been surpassed" << endl;
	Sleep(1000);
	cout << "The winner is ";
	cout << winner << endl;
	cout << "With a score of ";

	if (players[0]->returnID() == winner)
	{
		cout << gameTournament.getPlayerScore();
	}
	else
	{
		cout << gameTournament.getComputerScore();
	}

	cout << " points" << endl;
	Sleep(1000);
	cout << "game over" << endl;

}


