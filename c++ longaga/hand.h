#pragma once

#include <iostream>
#include <vector>
#include <string>

//This class will implement the layout of the project
class Hand
{
	std::vector<std::string> tiles;

public:
	Hand() {}


	//the player will display all cards in their hand
	void displayHand()
	{
		std::cout << "Hand: ";
		for (int i = 0; i < tiles.size(); i++)
		{
			std::cout << tiles[i] << " ";
		}
	}

	//this will remove a card from hand when the player draws
	void removeTile()
	{
		std::cout << std::endl;
	}

	void addTile(std::string tile)
	{
		tiles.push_back(tile);
	}

	
	void setTiles(std::vector<std::string> deal)
	{
		tiles = deal;
	}

	std::vector<std::string>& getHand() {
		return tiles;
	}


};