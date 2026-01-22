#pragma once

#include <iostream>
#include <vector>
#include "player.h"
using namespace std;

//This class will implement the layout of the project
class Round
{
	int roundNum = 1;

public:
	Round() {};

	void nextRound()
	{
		roundNum++;
	}

	void getRoundNum()
	{
		cout << "Round No.: " << roundNum << endl;
	}



};