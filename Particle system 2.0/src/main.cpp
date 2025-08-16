#include <raylib.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "Game.h"

struct ScreenStruct
{
    int width = 800;
    int height = 800;

    float fixedDeltaTime = 30;
    float timeScale = 1;

    float tick = 0;
};

ScreenStruct screen;

int main()
{
    //Inits a window, and sets a target fps
    //Creates a loop, that's running as long as the window is open
    InitWindow(screen.width, screen.height, "Raylib shmup");
    SetTargetFPS(120);
    SetExitKey(KEY_ESCAPE);

    Start();

    while(WindowShouldClose() == false)
    {
        //Creates a function thats run on a fixed timestep, specified in ScreenStruct
        screen.tick += GetFrameTime() * screen.timeScale;

        if(screen.tick > 1.0f / screen.fixedDeltaTime)
        {
            while(screen.tick > 1.0f / screen.fixedDeltaTime)
            {
                screen.tick -= 1.0f / screen.fixedDeltaTime;
                FixedUpdate(1.0f / screen.fixedDeltaTime);
            }
        }

        BeginDrawing();

        Update();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}