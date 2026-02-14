#pragma once

#include <iostream>
#include <vector>
#include <deque>
#include "layoutView.h"
using namespace std;


void LayoutView::display(deque<std::string> chain) {
    /*string top = "  ";
    string mid = "";
    string bot = "  ";

    //flush spaces in buffer before designing layout
    for (const string& tile : chain) {

        if (tile[0] == tile[2]) {
            cout << endl;

            // DOUBLE: center the number in 6 columns
            top += string(1, tile[0]); // 6
            mid += " | ";
            bot += string(1, tile[2]); // 6
        }
        else {
            // REGULAR: [1-2] + space = 6
            top += "      ";          // 6 spaces
            mid += tile + " ";        // 5 + 1 = 6
            bot += "      ";          // 6 spaces
        }
    }

    //cout << "|" << top << "|" << endl;
    //cout << "|" << mid << "|" << endl;
    //cout << "|" << bot << "|" << endl;

    cout << top << endl;
    cout << "L " << mid << " R" << endl;
    cout << bot << endl; */

    
    cout << "L ";
    for (int i = 0; i < chain.size(); i++)
    {
        cout << chain[i] << " ";
    }
    cout << "R";
    

}