/*
************************************************************
* Name: Jude Ghacibeh
* Project : Longaga C++
* Class : CMPS-366 OPL
* Date : 2/13/2026
************************************************************
*/

#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include "layoutView.h"
#include <iomanip>
using namespace std;


/* *********************************************************************
Function Name: display
Purpose: Renders the current domino layout (the chain) to the console
         in a visually structured format.
Parameters:
            chain: A deque of strings representing the sequence of
                   dominoes on the board. Passed by value.
Return Value: none
Algorithm:
            1) Initialize three empty strings: 'top', 'mid', and 'bot'
               to represent the three lines of console output.
            2) Iterate through each tile in the chain.
            3) If a tile is a double (e.g., "6-6"):
               a. Place the first digit in the 'top' row.
               b. Place a vertical separator '|' in the 'mid' row.
               c. Place the second digit in the 'bot' row.
            4) If a tile is standard (e.g., "5-4"):
               a. Place the full tile string in the 'mid' row.
               b. Add padding spaces to 'top' and 'bot' to maintain alignment.
            5) Print the three strings sequentially, prefixed with 'L'
               and suffixed with 'R' to indicate the layout edges.
Reference: Rendering logic for vertical doubles assisted by Gemini.
********************************************************************* */
void LayoutView::display(deque<std::string> tileChain) {

    string top = "";
    string mid = "";
    string bot = "";

    for (const string& tile : tileChain) {

        if (tile[0] == tile[2]) {
            cout << endl;

            top += " " + string(1, tile[0]) + " "; 
            mid += string("") + " | ";
            bot += " " + string(1, tile[2]) + " "; 
        }
        else {
            top += "    ";          // 6 spaces
            mid += tile + " ";        // 5 + 1 = 6
            bot += "    ";          // 6 spaces
        }
    }

    cout << "  " << top << endl;
    cout << "L " << mid << " R" << endl;
    cout << "  " << bot << endl;

}
    

