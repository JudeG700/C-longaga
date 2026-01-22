#pragma once

#include <iostream>
#include <vector>
using namespace std;

//This class will implement the layout of the project
class LayoutView
{

public:

	void display(deque<string> chain)
	{
		cout << "L ";
		for (int i = 0; i < chain.size(); i++)
		{
			cout << chain[i] << " ";
		}
		cout << "R";
	}
};