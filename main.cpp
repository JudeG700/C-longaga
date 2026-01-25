// c++ longaga.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include "layout.h"
#include "layoutView.h"
#include "stocks.h"
#include "hand.h"
#include "round.h"
#include "player.h"
#include "human.h"
#include "computer.h"
using namespace std;


string getEngine(vector<string> hand, string requiredEngine)
{
	string engine = "";

	for (int i = 0; i < hand.size(); i++)
	{
		if (hand[i] == requiredEngine)
		{
			engine = hand[i];
		}
	}

	return engine;

}

int main()
{

	//players
	Human human;
	Computer computer;

	Player* players[2];
	players[0] = &human;
	players[1] = &computer;

	int leftEnd = 6;
	int rightEnd = 6;


	//layout
	LayoutView layView;
	Layout layout;

	//rounds
	Round gameRound;

	//hands
	Hand humanHand;
	Hand computerHand;

	//stocks
	Stock gameStock;
	gameStock.shuffle();
	
	//give each hand 8 stocks
	

	vector<string> boneyard;

	LayoutView gameView;

	humanHand.setTiles(gameStock.deal());
	computerHand.setTiles(gameStock.deal());
	boneyard = gameStock.getBoneyard();



	//first is to get the engine
	//Check if any players have the engine

	//first, start with the human's hand
	vector<string> human_hand = humanHand.getHand();
	vector<string> computer_hand = computerHand.getHand();

	string engine = "";
	string requiredEngine = "";
	vector<string> requiredEngines = {"6-6", "5-5", "4-4", "3-3", "2-2", "1-1", "0-0"};
	int index = 0;
	requiredEngine = requiredEngines[index];

	string firstPlayer = "";
	engine = getEngine(human_hand, requiredEngine);

	if (engine == "")
	{
		cout << "Human doesn't have engine " << endl;
		engine = getEngine(computer_hand, requiredEngine);

		if (engine == "")
		{
			cout << "draw cards from boneyard" << endl;
		}
		else
		{
			cout << "Computer has engine" << endl;
			firstPlayer = "Computer";
		}

	}
	else
	{
		cout << "Human has engine" << endl;
		firstPlayer = "Human";
	}

	//help with chatgpt
	while (engine == "") {
		// Human tries to get engine
		string drawnTile = gameStock.drawTile();   // Stock gives a tile
		humanHand.addTile(drawnTile);              // Add to human hand
		cout << "Human draws: " << drawnTile << endl;

		if (drawnTile == requiredEngine) {
			engine = drawnTile;
			firstPlayer = "Human";
			break;
		}

		// Computer tries to get engine
		drawnTile = gameStock.drawTile();          // Stock gives a tile
		computerHand.addTile(drawnTile);           // Add to computer hand
		cout << "Computer draws: " << drawnTile << endl;

		if (drawnTile == requiredEngine) {
			engine = drawnTile;
			firstPlayer = "Computer";
			break;
		}
	}

	cout << firstPlayer << endl;
	cout << engine << endl;

	layout.addLeft(engine);

	bool isRoundOver = 0;

	cout << endl;
	int input;
	while (!isRoundOver)
	{
		cout << "_________________________" << endl;
		cout << "Tournament Score: 200" << endl;
		gameRound.getRoundNum();
		cout << endl;

		cout << "Computer: " << endl;
		cout << "	";
		computerHand.displayHand();
		cout << endl;
		cout << "	" << "Score: " << endl;
		cout << endl;

		cout << "Human: " << endl;
		cout << "	";
		humanHand.displayHand();
		cout << endl;
		cout << "	" << "Score: " << endl;
		cout << endl;

		cout << "Layout: " << endl;
		cout << "	";
		layView.display(layout.getChain());
		cout << endl;
		cout << endl;

		cout << "Boneyard: " << endl;
		gameStock.display();
		cout << endl;
		
		Move move = players[0]->takeTurn(humanHand, layout.returnLeft(), layout.returnRight());
		cout << move.tileIndex << endl;
		cout << move.side << endl;
		cout << move.draw << endl; 

		string tile = humanHand.getTileByIndex(move.tileIndex);
		//will add polymorphism for this later

		if (move.draw == true)
		{
			humanHand.addTile(gameStock.drawTile());
		}
		else
		{
			if (move.side == 'L')
			{
				if (layout.returnRight() == tile[0] - '0')
				{
					layout.addLeft(tile);
				}
				else
				{
					cout << "Incompatible tile, try again " << endl;
				}
			}
			else if (move.side == 'R')
			{
				if (layout.returnLeft() == tile[2] - '0')
				{
					layout.addRight(tile);
				}
				else
				{
					cout << "Incompatible tile, try again " << endl;
				}

			}

			humanHand.removeTile(move.tileIndex);
		}

		cout << layout.returnLeft() << endl;
		cout << layout.returnRight() << endl;

		move = players[1]->takeTurn(computerHand, layout.returnLeft(), layout.returnRight());
		
		if (move.draw)
		{
			humanHand.addTile(gameStock.drawTile());
		}
		else
		{
			if (move.side == 'L')
			{
				layout.addLeft(tile);
			}
			else if (move.side == 'R')
			{
				layout.addRight(tile);

			}

			computerHand.removeTile(move.tileIndex);
		}


	}
}

