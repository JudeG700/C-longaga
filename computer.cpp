#include "computer.h"
#include "hand.h"   // REQUIRED
#include <utility>

std::pair<int, int> Computer::parseTile(const std::string& tile)
{
    int dash = tile.find('-');
    int left = stoi(tile.substr(0, dash));
    int right = stoi(tile.substr(dash + 1));
    return { left, right };
}

std::vector<int> Computer::findPlayableTiles(int leftEnd, int rightEnd)
{
    std::vector<int> playable;
    auto& tiles = hand.getHand();   // works ONLY if getHand returns reference

    for (int i = 0; i < tiles.size(); i++)
    {
        auto p = parseTile(tiles[i]);
        int a = p.first;
        int b = p.second;

        if (a == leftEnd || a == rightEnd ||
            b == leftEnd || b == rightEnd)
        {
            playable.push_back(i);
        }
    }
    return playable;
}



Move Computer::takeTurn(Hand hand, int leftEnd, int rightEnd)
{
    Move move;
    auto& tiles = this->hand.getHand();
    std::vector<int> playable = findPlayableTiles(leftEnd, rightEnd);

    //If there are no predicted playable tiles, the computer will draw
    if (playable.empty()) {
        // No playable tiles — must draw from boneyard
        move.draw = true;
        return move;
    }

    int idx = playable[0];
    auto p = parseTile(tiles[idx]);
    int a = p.first;
    int b = p.second;

    move.tileIndex = idx;

    if (a == leftEnd || b == leftEnd)
        move.side = 'L';
    else
        move.side = 'R';

    move.draw = false;
    return move;
}