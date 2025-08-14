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

    float fixedTimeStep = 50;
    float timeScale = 1;
};

float timeStep;

ScreenStruct screen;

ParticleSystem_ parSystem;

Vector2 MouseTempPosition = {(float)screen.width / (float)2, (float)screen.height / (float)2};
Vector2 MouseTempVelocity = {0, 0};
Vector2 MouseTempPolarCoor = {0, 500};

void FixedUpdate()
{
    parSystem.UpdateParticles(1.0f / screen.fixedTimeStep, {screen.width/2, screen.height/2}, 10, true, screen.width, screen.height);
}

int main()
{
    InitWindow(screen.width, screen.height, "Raylib test");
    SetTargetFPS(30);
    for(int j = 0; j <= 10; j++)
    {
        for(int i = 0; i < 50; i++)
        {
            float dir = (GetRandomValue(-90, 90) + GetRandomValue(0, 180)) * DEG2RAD;
            float force = GetRandomValue(0, 500);

            parSystem.AddParticle({(float)screen.width/2, (float)screen.height/2}, {sin(dir) * force, cos(dir) * force}, fmax(GetRandomValue(-5, 3), 1), i);
        }
    }

    while(WindowShouldClose() == false)
    {
        timeStep += GetFrameTime() * screen.timeScale;
        if(timeStep > 1.0f / screen.fixedTimeStep)
        {
            while(timeStep > 0)
            {
                timeStep -= 1.0f / screen.fixedTimeStep;
                FixedUpdate();
            }
        }

        BeginDrawing();
            // ClearBackground(WHITE);
            DrawRectangle(0, 0, screen.width, screen.height, (Color){255, 255, 255, 255 / 10});

            parSystem.DrawParticles();
            // DrawCircleV(MouseTempPosition, 5, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}