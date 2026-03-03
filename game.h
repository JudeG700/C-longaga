#pragma once


#include "header.h"

/*
#include <iostream>
#include "player.h"
#include "hand.h"
#include "round.h"
#include "layout.h"
#include "layoutView.h"
#include "human.h"
#include "computer.h"
#include "tournament.h"
*/

using namespace std;

class Game
{
private:
	Player::Move move;


	//hands
	Hand humanHand;
	Hand computerHand;

	//players
	//Human human(humanHand);
	//Computer computer(computerHand);

	Human human;
	Computer computer;

	//polymorphism for players
	Player* players[2];
	//players[0] = &human;
	//players[1] = &computer;

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

public:

	Game();

	
	void runTournament(Tournament& gameTournament);
	void runRound(Round& gameRound, Layout& layout, Tournament& gameTournament, Player* players[], LayoutView& gameView);
	void startGame(int option);

	string showLoadMenu();
	void newLoadGameState(string filename);

	bool checkHandForTile(Player* p, string target);
	void saveGameState(string filename, Hand humanHand, Hand computerHand, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound);
	void loadGameState(string filename, Player* human, Player* computer, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound);
	void initSave(Hand humanHand, Hand computerHand, Stock& gameStock, Tournament& tournament, Layout& layout, Round& currentRound);
	bool applyMove(Player* player, Layout& layout, Stock& gamestock, Round& gameRound, Player::Move move);
	void addTotalPoints(Player& winner, Player& loser, Tournament& gameTournament);
	void tiePoints(Player* Human, Player* Computer, Tournament& gameTournament);
	string obtainEngine(Round gameRound, Player* players[], Stock& gameStock);
	void firstTurn(string engine, Layout& layout, Player* players[], Round& gameRound);


};