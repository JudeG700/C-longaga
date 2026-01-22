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

bool Computer::takeTurn(int leftEnd, int rightEnd)
{
    std::vector<int> playable = findPlayableTiles(leftEnd, rightEnd);
    return !playable.empty();
}
