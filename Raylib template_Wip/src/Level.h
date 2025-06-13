#pragma once

struct Block{
    int x;
    int y;

    int w;
    int h;

    bool IsPortal;
};

std::vector<Block> Blocks;

Player LoadLevel(int levelIndex, int BlockSize);
void DrawLevel();