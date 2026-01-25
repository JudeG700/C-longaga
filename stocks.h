#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <cstdlib>   
#include <ctime>     

using namespace std;

//This class will implement the layout of the project
class Stock
{
    vector<string> stocks;
    vector<string> boneyard;
    const short tiles = 8;

public:
    Stock() {
        for (int i = 0; i <= 6; i++) {
            for (int j = i; j <= 6; j++) {
                stocks.push_back(to_string(i) + "-" + to_string(j));
            }
        }
        srand(time(0)); // seed random
    }

    void display() {
        for (auto& tile : stocks)
            cout << tile << " ";
        cout << endl;
    }

    void shuffle() {
        int n = stocks.size();
        for (int i = n - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(stocks[i], stocks[j]);
        }
    }

    string drawTile() {
        if (stocks.empty()) return "";
        string tile = stocks.back();
        stocks.pop_back();
        return tile;
    }

    //we will use this 8 times for the player and 8 times for the computer
    vector<string> deal() {
        vector<string> hand;
        for (int i = 0; i < tiles && !stocks.empty(); i++) {
            hand.push_back(stocks.back());
            stocks.pop_back();
        }
        return hand;
    }

    vector<string> getBoneyard() {
        boneyard = stocks;
        return boneyard;
    }

    vector<string> getStock() {
        return stocks;
    }


    void reset() {
        stocks.clear();
        for (int i = 0; i <= 6; i++) {
            for (int j = i; j <= 6; j++) {
                stocks.push_back(to_string(i) + "-" + to_string(j));
            }
        }
        shuffle();
    }
};
