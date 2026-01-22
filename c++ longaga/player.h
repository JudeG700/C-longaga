#pragma once
#include "hand.h"

class Player {
protected:
    Hand hand;

public:
    virtual bool takeTurn(int leftEnd, int rightEnd) = 0;
    Hand& getHand()
    {
        return hand; 
    }
};

