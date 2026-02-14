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


#include "header.h"

/* *********************************************************************
Function Name: menu
Purpose: Displays the main menu and validates user input for game start options.
Parameters: none
Return Value: int, the selected option (1 for New Game, 2 for Load Game).
Algorithm:
			1) Display the "Longaga" title and options to the console.
			2) Prompt user for input.
			3) Repeat prompt if the input is outside the range of 1 to 2.
			4) Return the validated option.
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
	} while (option < 1 || option > 2);

	return option;
}

string showLoadMenu() {
	std::vector<std::string> saveFiles;
	WIN32_FIND_DATAA findFileData; // Added 'A' here

	// Using the 'A' version to avoid Unicode errors
	HANDLE hFind = FindFirstFileA("*.txt", &findFileData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::cout << "No save files found." << std::endl;
		return " ";
	}

	std::cout << "--- AVAILABLE SAVES ---" << std::endl;
	int count = 1;

	do {
		std::string filename = findFileData.cFileName;
		saveFiles.push_back(filename);
		std::cout << count << ") " << filename << std::endl;
		count++;
	} while (FindNextFileA(hFind, &findFileData) != 0); // Added 'A' here

	FindClose(hFind);

	int choice = -1;

	do
	{
		std::cout << "Select a file number to load: ";
		std::cin >> choice;
	} while (choice < 0 && choice > (int)saveFiles.size());
	
	string fileName = "";

	std::string selectedFile = saveFiles[choice - 1];
	std::cout << "Loading: " << selectedFile << "..." << std::endl;
	fileName = selectedFile;
	

	return fileName;
}

/* *********************************************************************
Function Name: checkHandForTile
Purpose: Searches a player's hand for a specific tile, checking both orientations.
Parameters:
			p: Pointer to the Player object.
			target: The tile string (e.g., "6-6") to find.
Return Value: bool, true if found, false otherwise.
********************************************************************* */
bool checkHandForTile(Player* p, string target) {
	if (p == nullptr) return false;

	// Get the hand from the player
	vector<string> hand = p->getHandTiles();

	// Create the flipped version of the tile (e.g., "1-2" becomes "2-1")
	string flipped = "";
	if (target.length() >= 3) {
		flipped += target[2];
		flipped += '-';
		flipped += target[0];
	}

	// Loop through the hand to see if either version exists
	for (const string& tile : hand) {
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
void saveGameState(string filename, Hand& playerHand, Hand& computerHand, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound) {

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
	for (auto const& tile : playerHand.getHandTiles()) outFile << tile << " ";
	outFile << "\n   Score: " << tournament.getPlayerScore() << "\n\n";

	outFile << "Layout:\n";
	outFile << "  L ";
	for (auto const& tile : layout.getChain()) outFile << tile << " ";
	outFile << "R\n\n";

	outFile << "Boneyard:\n";
	for (auto const& tile : gameStock.getBoneyard()) outFile << tile << " ";
	outFile << "\n\n";

	outFile << "Previous Player Passed: " << (currentRound.isPassed(currentRound.getNextPlayer()) ? "Yes" : "No") << "\n\n";

	// Assuming 0 is Human and 1 is Computer
	outFile << "Next Player: " << (currentRound.getCurrentPlayer() == 1 ? "Computer" : "Human") << "\n";

	cout << "Game saved to " << filename << endl;
	gameStock.reset();
	        // Very important so the board starts empty!

	outFile.close();

	exit(0);
}



/* *********************************************************************
Function Name: saveGameState
Purpose: Serializes the current game state into a JSON file using the Cereal library.
Parameters:
			playerHand, computerHand, gameStock, tournament, layout, currentRound.
			All passed by reference.
Return Value: none
Algorithm:
			1) Open an input file stream "gamestate.json".
			2) Initialize a Cereal JSONOutputArchive.
			3) Map each game object (hands, boneyard, layout, etc.) to a named JSON key.
			4) Close the archive and file stream.
			5) Terminate the program with exit(0) to fulfill "Save and Quit" requirement.
Reference: Google gemini
********************************************************************* */
void loadGameState (string filename, Hand& playerHand, Hand& computerHand, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound) {
	std::ifstream is(filename);
	if (!is) return;

	std::string line;
	while (std::getline(is, line)) {
		// 1. Tournament Score
		if (line.find("Tournament Score:") != std::string::npos) {
			tournament.setTournScore(std::stoi(line.substr(line.find(":") + 1)));
		}
		// 2. Round Number
		else if (line.find("Round No.:") != std::string::npos) {
			currentRound.setRoundNum(std::stoi(line.substr(line.find(":") + 1)));
		}
		// 3. Computer Hand (This is the tricky one)
		else if (line.find("Computer:") != std::string::npos) {
			std::getline(is, line); // Move to the "Hand:" line
			std::string tilesStr = line.substr(line.find(":") + 2);

			stringstream ss(tilesStr);
			string tempTile;
			vector<string> loadedTiles;

			while (ss >> tempTile) { // This automatically splits by spaces
				loadedTiles.push_back(tempTile);
			}
			computerHand.setTiles(loadedTiles);

			std::getline(is, line);
			if (line.find("Score:"))
			{
				int scoreVal = std::stoi(line.substr(line.find(":") + 2));
				tournament.setComputerScore(scoreVal);

			}

		}
		// 4. Human Hand
		else if (line.find("Human:") != std::string::npos) {

			std::getline(is, line); // Move to "Hand:" line
			std::string tilesStr = line.substr(line.find(":") + 2);

			stringstream ss(tilesStr);
			string tempTile;
			vector<string> loadedTiles;

			while (ss >> tempTile) { // This automatically splits by spaces
				loadedTiles.push_back(tempTile);
			}
			playerHand.setTiles(loadedTiles);

			std::getline(is, line);
			if (line.find("Score:"))
			{
				int scoreVal = std::stoi(line.substr(line.find(":") + 2));
				tournament.setHumanScore(scoreVal);
			}
			// Same logic for humanHand
		}
		else if (line.find("Layout:") != std::string::npos)
		{
			if (std::getline(is, line) && line.find("L") != std::string::npos) {
				// Find the text between L and R
				size_t start = line.find("L") + 2;
				size_t end = line.find("R");
				if (start < end && end != std::string::npos) {
					std::string tilesStr = line.substr(start, end - start);
					stringstream ss(tilesStr);
					string temp;
					while (ss >> temp) layout.addLeft(temp);
				}
			}
		}
		else if (line.find("Boneyard:") != std::string::npos)
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
		else if (line.find("Previous Player Passed:") != std::string::npos) {
			string val = line.substr(line.find(":") + 2); // Get "Yes" or "No"
			currentRound.setPassed(val == "Yes");
		}
		else if (line.find("Next Player:") != std::string::npos) {
			string nextName = line.substr(line.find(":") + 2); // Jump past ": "
			if (nextName.find("Computer") != std::string::npos) {
				currentRound.setNextPlayer(1);
			}
			else if (nextName.find("Human") != std::string::npos) {
				currentRound.setNextPlayer(0);
			}
			else
			{
				currentRound.setNextPlayer(0);
			}
		}
	}
	is.close();
}


/**
 * @brief Prompt-driven wrapper for saveGameState.
 * Allows the user to save and exit the application safely after each player takes a turn and after a round is over
 */
void initSave(Hand& playerHand, Hand& computerHand, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound)
{
	int inp;
	do
	{
		cout << "Would you like to save?" << endl;
		cout << "1. Yes " << endl;
		cout << "2. No " << endl;
		cout << "Note: Saving here will exit the game " << endl;
		cin >> inp;

	} while (inp < 1 || inp > 2);


	if (inp == 1)
	{
		string fileName;
		cout << "Enter name for save file (e.g., game1.txt): ";
		cin >> fileName;
		saveGameState(fileName, playerHand, computerHand, gameStock, tournament, layout, currentRound);
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
	Move move
) {

	//if you were to select help in the move function
	if (move.help)
	{
		/*Since help isn't a move, it returns false so that the player
		*can make their move after the assistance they received 
		*/
		Computer helper;
		//void Computer::help(Player player, Stock gamestock, Round gameRound, int leftEnd, int rightEnd)

		helper.help(player, gamestock, gameRound, layout.returnLeft(), layout.returnRight());

		return false;+
	}

	//if the player decided to draww
	if (move.draw) {

		//for human players
		if (move.hasPlayableTiles)
		{
			cout << "Sorry. You can't draw unless you have no playable tiles" << endl;
			return false;
		}

		//check if the boneyard isn't empty
		if (!gamestock.getBoneyard().empty()) {
			player->addTile(gamestock.drawTile());
			cout << player->returnID() << " drew a tile." << endl;
			return true;   
		}
		//if it is empty, player can't draw
		//in the case of the computer, it will decide if it draws in a previous function
		else {
			cout << "Boneyard empty. Can't draw." << endl;
			cout << "Returning..." << endl;
			return false;
		}
	}

	//if they decide to pass, the next player takes their turn
	if (move.passed) {

		cout << "Human player has passed" << endl;
		return true;
	} 

	
	const vector<string>& tiles = player->getHandTiles();

	// If someone were to pick an index that is out of bounds
	if (move.tileIndex < 0 || move.tileIndex >= tiles.size()) {
		cout << "Invalid tile index" << endl;
		cout << "Returning..." << endl;
		return false;
	}

	string tile = tiles[move.tileIndex];

	//coonvert selected tile to ints for both sides

	//get the left end of the tile
	int a = tile[0] - '0';

	//get the right end of the tile
	int b = tile[2] - '0';

	//get left and right end
	int leftEnd = layout.returnLeft();
	int rightEnd = layout.returnRight();
	
	bool placed = false;
	bool isDouble = (a == b);

	//Adds the tiles
	//doubles can be added anywhere, but others must have matching numbers with the left end or right end
	if (move.side == 'L') {

		//we need logic to flip tiles as well
		
		if (isDouble)
		{
			layout.addLeft(tile);
		}
		else if (b == leftEnd) //if b matches
		{
			layout.addLeft(tile);
			cout << "Human player has added: " << tile << " on left side of layout " << endl;

		}
		else if (a == leftEnd) { //if side a matches
			string flipped = ""; flipped += tile[2]; flipped += '-'; flipped += tile[0];
			cout << "Flipped left: " << flipped << endl;
			cout << "Human player has added: " << tile << " on left side of layout " << endl;
			layout.addLeft(flipped); 
		}
		

	}
	else if (move.side == 'R') {

		if (isDouble)
		{
			layout.addRight(tile);
		}
		else if (a == rightEnd)
		{
			layout.addRight(tile);
			cout << "Human player has added: " << tile << " on right side of layout " << endl;

		}
		else if (b == rightEnd) {
			string flipped = ""; flipped += tile[2]; flipped += '-'; flipped += tile[0];
			cout << "Flipped right: " << flipped << endl;
			cout << "Human player has added: " << tile << " on right side of layout " << endl;

			layout.addRight(flipped);
		}

	}


	//SECTION BUILT USING GEMINI 

	//this is just used to document the moves that the computer makes
	if (player->returnID() == "Computer")
	{
		
		string tilePlayed = tiles[move.tileIndex];
		string sideName = (move.side == 'L') ? "left" : "right";

		string referencePoint = (layout.getChain().size() <= 1) ? "engine" : "layout";
		
		if (move.draw) {
			// Already handled in your DRAW block
		}
		else if (move.passed) {
			cout << player->returnID() << " passed." << endl;
		}
		else {
			// The specific output you wanted:
			cout << "The " << player->returnID() << " placed " << tilePlayed
				<< " to the " << sideName << " of the " << referencePoint << "." << endl;

		}
	}
	

	//Remove the tile from the player's hand after it has been deposited
	player->removeTile(move.tileIndex);
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
		gameTournament.addPlayerScore(total);
	}
	else if(winner.returnID() == "Computer")
	{
		gameTournament.addComputerScore(total);
	}

	
} 


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

			// Inside obtainEngine
			/*int activeIdx = gameRound.getCurrentPlayer(); // 0 for Human, 1 for Computer
			vector<string> hand = players[activeIdx]->getHandTiles();

			for (int i = 0; i < hand.size(); i++) {
				if (hand[i] == engine) {
					players[activeIdx]->removeTile(i);
					cout << "DEBUG: Removed " << engine << " from " << players[activeIdx]->returnID() << endl;
					break;
				}
			} */

			//gameRound.setCurrentPlayer(0);
		}

	}
	else
	{
		cout << "Human has engine" << endl;
		cout << "Human takes first turn" << endl;
		// Inside obtainEngine
		/*int activeIdx = gameRound.getCurrentPlayer(); // 0 for Human, 1 for Computer
		vector<string> hand = players[activeIdx]->getHandTiles();

		for (int i = 0; i < hand.size(); i++) {
			if (hand[i] == engine) {
				players[activeIdx]->removeTile(i);
				cout << "DEBUG: Removed " << engine << " from " << players[activeIdx]->returnID() << endl;
				break;
			}
		} */


		//this automatically made the move already so current player is the next player now
		//gameRound.setCurrentPlayer(1);
	}



	//if no player has the engine, they will both keep drawing tiles until they receive one
	//The player that receives the engine first will go first
	while (engine == "") {

		string humanDraw, compDraw;
		// Human tries to retrieve engine
		humanDraw = gameStock.drawTile();   // Stock gives a tile
		players[0]->addTile(humanDraw);              // Add to human hand
		cout << "Human draws: " << humanDraw << endl;

		// Computer tries to retrieve engine
		compDraw = gameStock.drawTile();          // Stock gives a tile
		players[1]->addTile(compDraw);           // Add to computer hand
		cout << "Computer draws: " << compDraw << endl;


		if (humanDraw == gameRound.getRequiredEngine()) {
			engine = humanDraw;

			break;
		}


		if (compDraw == gameRound.getRequiredEngine()) {
			engine = compDraw;


			break;
		}
	}


	return engine;

}

int main()
{
	//unused
	BlockedNumbersMemory blockedNums;

	//move object used for documenting moves
	Move move;

	//Tournament
	Tournament gameTournament;


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
	LayoutView layView;
	Layout layout;


	//ends of the layout
	int leftEnd;
	int rightEnd;

	//rounds
	Round gameRound;

	//stocks
	Stock gameStock;

	//give each hand 8 stocks

	//Rounds
	Round rounds;


	LayoutView gameView;



	//first is to get the engine
	//Check if any players have the engine



	int option = menu();

	//if player chose to load game
	bool gameLoaded = (option == 2);
	
	//nothing is added to the layout yet
	leftEnd = 0;
	rightEnd = 0;
	bool gameWon = 0;

	//Continues looping until the tournament score is reached
	while (gameTournament.getPlayerScore() < gameTournament.getTournScore() && gameTournament.getComputerScore() < gameTournament.getTournScore())
	{

		//if player chose to start a new game
		if (gameLoaded == false)
		{
			gameStock.shuffle();

			players[0]->setTiles(gameStock.deal());
			players[1]->setTiles(gameStock.deal());

			/*
			string engine = "";
			// 1. Identify who has it
			// 1. Check hands first - DO NOT DRAW YET
			engine = gameRound.determineEngine(players[0]->getHandTiles());
			if (engine != "") {
				cout << "Human has engine. Human takes first turn." << endl;
				gameRound.setCurrentPlayer(0);
			}
			else {
				engine = gameRound.determineEngine(players[1]->getHandTiles());
				if (engine != "") {
					cout << "Computer has engine. Computer takes first turn." << endl;
					gameRound.setCurrentPlayer(1);
				}
			}

			// 2. ONLY draw if the engine was NOT found in starting hands
			if (engine == "") {
				while (true) {
					// Human draws
					string drawnTile = gameStock.drawTile();
					players[0]->addTile(drawnTile);
					cout << "Human draws: " << drawnTile << endl;
					if (drawnTile == gameRound.getRequiredEngine()) {
						engine = drawnTile;
						gameRound.setCurrentPlayer(0);
						break;
					}

					// Computer draws
					drawnTile = gameStock.drawTile();
					players[1]->addTile(drawnTile);
					cout << "Computer draws: " << drawnTile << endl;
					if (drawnTile == gameRound.getRequiredEngine()) {
						engine = drawnTile;
						gameRound.setCurrentPlayer(1);
						break;
					}
				}
			}

			// 3. Place the engine from the CORRECT player's hand
			int activeIdx = gameRound.getCurrentPlayer();
			vector<string> activeHand = players[activeIdx]->getHandTiles();
			int tilePos = -1;
			for (int i = 0; i < activeHand.size(); i++) {
				if (activeHand[i] == gameRound.getRequiredEngine()) {
					tilePos = i;
					break;
				}
			}

			if (tilePos != -1) {
				layout.addLeft(engine);
				players[activeIdx]->removeTile(tilePos);
				leftEnd = layout.returnLeft();
				rightEnd = layout.returnRight();
			}

			*/

			string engine = "";
			engine = obtainEngine(gameRound, players, gameStock);

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


			humanHand = players[0]->getHand();
			computerHand = players[1]->getHand();

			
			vector<string> humanTiles = humanHand.getHandTiles();
			vector<string> computerTiles = computerHand.getHandTiles();


			if (gameWon)
			{

				//humanHand.setTiles(players[0]->getHandTiles());
				//computerHand.setTiles(players[1]->getHandTiles());

				humanHand = players[0]->getHand();
				computerHand = players[1]->getHand();

				//saves it too a copy
				initSave(humanHand, computerHand, gameStock, gameTournament, layout, gameRound);
			}

		}

		//if the player loads the game, sync previous data with all objects
		else if (gameLoaded == true)
		{
			
			
			cout << "resuming loaded game " << endl;
			//int loadnum;
			//cout << "Enter the number of the file to resume: ";
			string loadName = "";
			if ((loadName = showLoadMenu()) == " ")
			{
				menu();
			}
			loadGameState(loadName, humanHand, computerHand, gameStock, gameTournament, layout, gameRound);
			players[0]->setTiles(humanHand.getHandTiles());
			players[1]->setTiles(computerHand.getHandTiles());

			if (layout.isEmpty())
			{
				string engine = "";
				engine = obtainEngine(gameRound, players, gameStock);
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

			leftEnd = layout.returnLeft();
			rightEnd = layout.returnRight();
			
			
			gameLoaded = false;
		}
		
		
		

		cout << "Get ready for round " << gameRound.getRoundNum() << endl;
		Sleep(2000);


		//determine if player placed a tile
		bool placedTile[2] = { false, false };


		//while current round isn't over
		while (!gameRound.isRoundOver())
		{
			//current and next player's index (0 and 1)
			int currIdx = gameRound.getCurrentPlayer();
			int nextIdx = 1 - currIdx;
			
			cout << "CURRENT FUCKING INDEX: " << currIdx << endl;
			cout << "NEXT FUCKING INDEX: " << nextIdx << endl;

			//set next player
			gameRound.setNextPlayer(nextIdx);

			cout << "_________________________" << endl;
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
			layView.display(layout.getChain());
			cout << endl;
			cout << endl;

			cout << "Boneyard: " << endl;
			gameStock.display();
			cout << endl;

			cout << "Previous Player Passed: " << gameRound.yesNo(gameRound.isPassed(gameRound.getNextPlayer())) << endl;
			cout << endl;
			cout << "Next Player: " << players[nextIdx]->returnID() << endl;
			
			
			if (gameRound.getCurrentPlayer() == 0)
			{
				cout << "Press 4 for help" << endl;
			}




			//to ensure move function returns true
			bool moveWasSuccessful = 0;

			//move object to store move details from move.h
			Move move;


			do
			{
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
				

				//apply the move
				moveWasSuccessful = applyMove(players[gameRound.getCurrentPlayer()], layout, gameStock, gameRound, move);
				

				//update the ends
				leftEnd = layout.returnLeft();
				rightEnd = layout.returnRight();


				//if a player chose to pass
				if (move.passed)
				{
					gameRound.setPassed(gameRound.getCurrentPlayer());


					//blocked nums
					vector<string>boneyard = gameStock.getBoneyard();
					blockedNums.addBlockedNums(layout.returnLeft(), layout.returnRight());

					

					//if both pass, we need to ensure the boneyard's empty before we end the round
					if (gameRound.bothPassed() && boneyard.empty())
					{
						cout << "Both players have passed. Both win";

						tiePoints(players[0], players[1], gameTournament);
						gameRound.roundOver();

						//reset passes for next round
						gameRound.resetPasses();

						break;
					}
					
				}
				else //reset the pass
				{
					if (gameRound.isPassed(gameRound.getCurrentPlayer()))
					{
						gameRound.resetPass(gameRound.getCurrentPlayer());
					}
				}

				
				

			} while (!moveWasSuccessful);

			//otherwise, we keep going
			humanHand = players[0]->getHand();
			computerHand = players[1]->getHand();


			//player placed a tile
			placedTile[gameRound.getCurrentPlayer()] = 1;

			//if either hand is empty, the round ends and the winner is determined
			if (players[0]->getHandTiles().empty() || players[1]->getHandTiles().empty())
			{
				break;
			}
			
			//if both players take their turn, ensure to offer human player to save
			if (placedTile[0] == 1 && placedTile[1] == 1)
			{
				//initSave(humanHand, computerHand, gameStock, gameTournament, layout, gameRound);
				placedTile[0] = 0;
				placedTile[1] = 0;
			}
			//Sleep(2000);


			//currentPlayer = nextPlayer;
			gameRound.setCurrentPlayer(nextIdx);

		} 

		//check the winner of the round when it ends
		if (!gameRound.bothPassed())
		{
			Player* winner = gameRound.checkWinner(players[0], players[1]);

  			if (winner != nullptr)
			{
				Player* human = players[0];
				Player* computer = players[1];

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

				addTotalPoints(*winner, *loser, gameTournament);

			}
				//help from chatgpt when running bug check

		}
		
		//make the engine be the next engine
		gameRound.incEIndex();

		//increment round number
		gameRound.nextRound();

		//the required engine is the engine lower than the first
		gameRound.setRequiredEngine();

		//clear chain
		layout.clearChain();

		//add score
		//gameTournament.addPlayerScore(players[0]->getScore());
 		//gameTournament.addComputerScore(players[1]->getScore());
		players[0]->emptyHand();
		players[1]->emptyHand();


		cout << endl;
		cout << "TOTAL POINTS: " << endl;
		cout << "HUMAN: " << gameTournament.getPlayerScore() << endl;
		cout << "COMPUTER: " << gameTournament.getComputerScore() << endl;
		Sleep(3000);
		

		gameStock.reset();

		//offer player to save when round ends
		gameWon = 1;
	}


	string winner = gameTournament.determineWinner();
	cout << "Tournament is over: " << endl;
	cout << "The winner is: " << endl;
	cout << winner << endl;
	cout << "Score: " << endl;

	if (players[0]->returnID() == winner)
	{
		cout << gameTournament.getPlayerScore() << endl;
	}
	else
	{
		cout << gameTournament.getComputerScore() << endl;
	}

}


