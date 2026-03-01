#pragma once

#include <iostream>
#include <vector>
using namespace std;


/* *********************************************************************
Class Name: Layoutview
Purpose: Displays the sequence of tiles managed by layout. Seen by both
players to check the board and to place tiles.
********************************************************************* */
class LayoutView
{

public:

	void display(deque<string> tileChain);
};