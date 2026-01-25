#pragma once

#include <iostream>
#include <deque>
using namespace std;

//This class will implement the layout of the project
class Layout
{
public:

	deque<string> dominoChain;

	void addRight(string tile)
	{
		dominoChain.push_back(tile);
	}

	int returnLeft()
	{
		return dominoChain.front()[0] - '0';
	}

	int returnRight()
	{
		return dominoChain.back()[2] - '0';

	}

	void addLeft(string tile)
	{
		dominoChain.push_front(tile);
	}

	void clearChain()
	{
		dominoChain.clear();
	}

	deque<string> getChain()
	{
		return dominoChain;
	}


};