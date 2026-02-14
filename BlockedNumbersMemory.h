#pragma once

#include "player.h"
#include "hand.h"
#include <vector>
#include <string>
#include <set>

// memory component only for AI
class BlockedNumbersMemory {
private:
    std::set<int> blockedNumbers;
public:
    void addBlockedNums(int left, int right) {
        blockedNumbers.insert(left);
        blockedNumbers.insert(right);
    }
    void remove(int num) { blockedNumbers.erase(num); }
    std::set<int> get() const { return blockedNumbers; }
};

