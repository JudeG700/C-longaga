#pragma once
#include "player.h"
#include "hand.h"
#include <iostream>

class Human : public Player {


public:
    Human() = default;

    Move takeTurn(Hand hand, int leftEnd, int rightEnd) override;  // declared here
};
