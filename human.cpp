#include "human.h"
#include <iostream>
#include "hand.h"

using namespace std;


Move Human::takeTurn(Hand hand, int leftEnd, int rightEnd) {
    Move move;


    int choice;
    do {
        cout << "1=Play 2=Draw: ";
        cin >> choice;
    } while (choice != 1 && choice != 2);

    if (choice == 1) {
        move.draw = false;
        do {
            cout << "Tile index (0-" << hand.getHand().size() - 1 << "): ";
            cin >> move.tileIndex;
        } while (move.tileIndex < 0 || move.tileIndex >= hand.getHand().size());

        do {
            cout << "Side (L/R): ";
            cin >> move.side;
        } while (move.side != 'L' && move.side != 'R');

    }
    else {
        move.draw = true;
    }

    return move;
}
