#include <raylib.h>
#include <iostream>
#include <vector>

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
        "_@_______a",
        "aaaaaaaaaa",
    },

    {
        "_+________",
        "_a________",
        "__________",
        "___a______",
        "__________",
        "_____a____",
        "__________",
        "_______a__",
        "__________",
        "_________a",
        "_@________",
        "aaaaaaaaaa",
    },

    {
        "____@_____",
        "__________",
        "__________",
        "aaaaaaaaaa",
        "____+_____",
    },
};

Player LoadLevel(int levelIndex, int BlockSize)
{
    Blocks.clear();

    char p = '@';
    char b = 'a';
    char e = '+';

    Vector2 playerPos = {0, 0};

    for(int i = 0; i < (int)Levels[levelIndex].size(); i++)
    {
        for(int j = 0; j < (int)Levels[levelIndex][i].size(); j++)
        {
            char l = Levels[levelIndex][i][j];

            if(l == p)
            {
                playerPos = {(float)j * BlockSize, (float)i * BlockSize};
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

    return AddPlayer(playerPos, {0, 0}, {0, 9.81f}, 5, 0, 0.95f, 8, 10, 300, true);
};

Block GetBlock(int index)
{
    return Blocks[index];
};

int GetBlocksLength()
{
    return Blocks.size();
};

void DrawLevel()
{
    for(Block block : Blocks)
    {
        DrawRectangle(block.x, block.y, block.w, block.h, block.IsPortal ? (Color){255, 0, 255, 255} : WHITE);
    }
};