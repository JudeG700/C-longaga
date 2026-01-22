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