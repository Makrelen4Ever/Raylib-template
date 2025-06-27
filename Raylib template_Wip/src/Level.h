#pragma once

struct Block{
    int x;
    int y;

    int w;
    int h;

    bool IsPortal;
    bool IsDangerous;

    Color color;
};

static std::vector<Block> Blocks;

Player LoadLevel(int levelIndex, int BlockSize);
void DrawLevel();

Block GetBlock(int index);

int GetBlocksLength();