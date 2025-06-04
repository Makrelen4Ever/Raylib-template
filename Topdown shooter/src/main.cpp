#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "InputManager.h"
#include "Player.h"

struct ScreenStruct
{
    float width = 1920;
    float height = 1080;
};

ScreenStruct screen;

Player player = AddPlayer({screen.width/2, screen.height/2}, {0, 0}, 0.2f, 0, 0.999f);

void FixedUpdate()
{
    player.Move();
    player.ApplyDrag();

    player.Update();
};

void Update()
{
    player.DrawPlayer();
};

int main()
{
    InitWindow(screen.width, screen.height, "Raylib test");
    // SetTargetFPS(120);

    float tick;

    while(WindowShouldClose() == false)
    {
        Update();

        tick += GetFrameTime();

        if(tick >= 1/50)
        {
            tick = 0;
            FixedUpdate();
        }

        BeginDrawing();
        ClearBackground((Color){50, 50, 50, 255});
        DrawFPS(10, 10);

        Update();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}