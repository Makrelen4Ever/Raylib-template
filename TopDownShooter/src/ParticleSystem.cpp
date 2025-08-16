#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
#include <math.h>

#include "ParticleSystem.h"

//Declaring a functino to add particles.
void ParticleSystem_:: AddParticle(Vector2 pos, Vector2 vel)
{
    Particle particle;

    particle.pos = pos;
    particle.vel = vel;

    particle.age = 5;

    ParticleSystem_::Particles.push_back(particle);
}

void ParticleSystem_::UpdateParticles(float deltaTime)
{

    parCount = -1;
    for(Particle &particle : Particles)
    {
        parCount++;

        //Movement
        particle.pos = Vector2Add(particle.pos, Vector2Scale(particle.vel, deltaTime));

        particle.age -= deltaTime;
        if(particle.age <= 0)
        {
            ParticleSystem_::Particles.erase(Particles.begin() + parCount);
        }
    }
}

void ParticleSystem_::DrawParticles()
{
    for(Particle particle : Particles)
    {
        DrawPixelV(particle.pos, BLACK);
    }
}