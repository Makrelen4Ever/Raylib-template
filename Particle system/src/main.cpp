#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "ParticleSystem.h"

struct ScreenStruct
{
    int width = 1920;
    int height = 1080;

    float fixedTimeStep = 64;
};

float timeStep;

ScreenStruct screen;

ParticleSystem_ parSystem;

void FixedUpdate()
{
    parSystem.UpdateParticles(1.0f / screen.fixedTimeStep, GetMousePosition(), 1000);
}

int main()
{
    InitWindow(screen.width, screen.height, "Raylib test");

    while(WindowShouldClose() == false)
    {
        if(IsMouseButtonDown(0))
        {
            for (int i = 0; i < 2; i++)
            {
                parSystem.AddParticle(GetMousePosition(), Vector2Scale(GetMouseDelta(), (float)GetRandomValue(0, 100)));
            }
        }

        timeStep += GetFrameTime();
        if(timeStep > 1.0f / screen.fixedTimeStep)
        {
            while(timeStep > 0)
            {
                timeStep -= 1.0f / screen.fixedTimeStep;
                FixedUpdate();
            }
        }

        BeginDrawing();
            ClearBackground((Color){50, 50, 50, 255});
            DrawFPS(10, 10);

            parSystem.DrawParticles();

        EndDrawing();
    }

    CloseWindow();
    return 0;
}