#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>
#include <math.h>

#include "ParticleSystem.h"

struct ScreenStruct
{
    int width = 1920/2;
    int height = 1080/2;

    float fixedTimeStep = 40;
};

float timeStep;

ScreenStruct screen;

ParticleSystem_ parSystem;

void FixedUpdate()
{
    parSystem.UpdateParticles(1.0f / screen.fixedTimeStep, GetMousePosition(), 100, false, screen.width, screen.height);
}

int main()
{
    InitWindow(screen.width, screen.height, "Raylib test");

    for(int i = 0; i < 100000; i++)
    {
        int dir = GetRandomValue(0, 360);
        int force = GetRandomValue(0, 50);

        parSystem.AddParticle({screen.width/2, screen.height/2}, {sin(dir) * force, cos(dir) * force}, Clamp(GetRandomValue(-20, 5), 1, 1), i);
    }

    while(WindowShouldClose() == false)
    {
        parSystem.AddParticle({0, screen.height/2}, {100, 50}, 1, parSystem.parCount + 1);

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