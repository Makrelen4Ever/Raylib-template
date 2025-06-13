#include <raylib.h>
#include <iostream>
#include <vector>

// using namespace std;

#include "GenericStructs.h"
#include "Rigidbody.h"
#include "Player.h"
#include "Level.h"

std::vector<std::vector<std::string>> Levels = {
    {
        "@_____",
        "____+_",
        "aaaaaa",
    },

    {
        "+_________",
        "aaa_______",
        "_______aaa",
        "_@________",
        "aaaaaaaaaa",
    },
};

Player LoadLevel(int levelIndex, int BlockSize)
{
    Blocks.clear();

    char p = '@';
    char b = 'a';
    char e = '+';

    Vector2 playerPos;

    for(int i = 0; i < Levels[levelIndex].size(); i++)
    {
        for(int j = 0; j < Levels[levelIndex][i].size(); j++)
        {
            auto l = Levels[levelIndex][i][j];

            if(l == p)
            {
                playerPos = {j * BlockSize, i * BlockSize}; //AddPlayer({j * BlockSize, i * BlockSize}, {0, 0}, {0, 9.81f}, 5, 0, 0.95f, 1, 1, true);
            }else if(l == b)
            {
                Block instance = {j * BlockSize, i * BlockSize, BlockSize, BlockSize, false};
                Blocks.push_back(instance);
            }else if(l == e)
            {
                Block instance = {j * BlockSize, i * BlockSize, BlockSize, BlockSize, true};
                Blocks.push_back(instance);
            }else
            {
                continue;
            }
        }
    }

    return AddPlayer(playerPos, {0, 0}, {0, 9.81f}, 5, 0, 0.95f, 1, 1, true);;
};

void DrawLevel()
{
    for(Block block : Blocks)
    {
        DrawRectangle(block.x, block.y, block.w, block.h, block.IsPortal ? (Color){255, 0, 255, 255} : WHITE);
    }
}