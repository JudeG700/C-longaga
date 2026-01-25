// move.h
#pragma once

struct Move {
    int tileIndex;
    char side;   // 'L' or 'R'
    bool draw;   // true if drawing from boneyard
};
