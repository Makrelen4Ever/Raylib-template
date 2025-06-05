#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <math.h>


#include "src/Generics/GenericStructs.h"
#include "src/Generics/Rigidbody.h"
#include "src/Generics/InputManager.h"
#include "src/Player.h"

struct ScreenStruct
{
    float width = 1920;
    float height = 1080;
};

ScreenStruct screen;

Player player = AddPlayer({screen.width/2, screen.height/2}, {0, 0}, 10.0f, 0, 0.95f, 1);

void FixedUpdate()
{
    player.Move();
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

    int i = 0;

    while(WindowShouldClose() == false)
    {
        Update();

        tick += GetFrameTime();
        i++;

        if(tick >= 0.02f)
        {
            tick = 0;

            std::cout << 1.0f/((float)i / (float)GetFPS()) << std::endl;
            i = 0;
            
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