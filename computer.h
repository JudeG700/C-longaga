#pragma once
#include "player.h"
#include <vector>
#include <string>

class Computer : public Player {
public:
    Move takeTurn(Hand hand, int leftEnd, int rightEnd) override;

private:
    std::pair<int, int> parseTile(const std::string& tile);
    std::vector<int> findPlayableTiles(int leftEnd, int rightEnd);
};
