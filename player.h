#pragma once
#include "hand.h"
#include <vector>
#include "move.h"


class Player {
protected:
    Hand hand;
    

public:
    
    virtual Move takeTurn(Hand hand, int leftEnd, int rightEnd) = 0;
    Hand& getHand()
{
        return hand; 
    }
};

