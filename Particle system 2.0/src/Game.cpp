#include "Game.h"

ScreenStruct screen;
ParticleSystem_ particleSystem;

void Start()
{
    Particle particle;

    particle.Position = {0, 0};
    particle.Velocity = {0, 0};
    particle.Forces = {0, 0};

    particle.Age = 1000;
    particleSystem.ReloadParticle(particle);

    float dir, force;

    for(int i = 0; i <= 1000; i++)
    {
        dir = (float)GetRandomValue(0, 3600) / 10 * DEG2RAD;
        force = GetRandomValue(0, 2000) / 10;
        particleSystem.AddParticle({(float)screen.width / 2.0f, (float)screen.height / 2.0f}, {sin(dir) * force, cos(dir) * force}, {0, 0});
    }
}

void Update()
{
    // ClearBackground(WHITE);
    DrawRectangle(0, 0, screen.width, screen.height, (Color){255, 255, 255, 255 / 10});
    DrawFPS(10, 10);

    particleSystem.DrawParticles();
}

void FixedUpdate(float deltaTime)
{
    particleSystem.UpdateParticles(false, deltaTime, -100, 250);
}