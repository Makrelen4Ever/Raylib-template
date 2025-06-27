#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
#include <math.h>

#include "ParticleSystem.h"

void ParticleSystem_:: AddParticle(Vector2 pos, Vector2 vel)
{
    Particle particle;

    particle.pos = pos;
    particle.vel = vel;

    particle.age = 0;

    ParticleSystem_::Particles.push_back(particle);
}

void ParticleSystem_::UpdateParticles(float deltaTime, Vector2 target, float forceMult)
{
    int i = -1;

    for(Particle &particle : Particles)
    {
        i++;

        float dx;
        float dy;

        float dist;

        Vector2 normal;

        dx = particle.pos.x - target.x;
        dy = particle.pos.y - target.y;

        dist = sqrt((dx * dx) + (dy * dy));
        // dist = fmax(dist, 10);

        normal = {dx * (1 / dist), dy * (1 / dist)};

        particle.vel.x -= normal.x / dist * forceMult;
        particle.vel.y -= normal.y / dist * forceMult;

        // particle.vel = Vector2Add(particle.vel, Vector2Scale({0, 627.84f}, deltaTime));
        particle.pos = Vector2Add(particle.pos, Vector2Scale(particle.vel, deltaTime));

        particle.age += deltaTime;

        if(particle.age > 60 || dist > 10000)
        {
            Particles.erase(Particles.begin() + i);
        }
    }
}

void ParticleSystem_::DrawParticles()
{
    for(Particle particle : Particles)
    {
        DrawPixelV(particle.pos, WHITE);
    }
}