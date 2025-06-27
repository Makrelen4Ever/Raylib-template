#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>

#include "ParticleSystem.h"

void ParticleSystem_:: AddParticle(Vector2 pos, Vector2 vel, std::vector<Vector2> externalForces, float size)
{
    Particle particle;

    particle.pos = pos;
    particle.vel = vel;

    particle.size = size;

    particle.age = 0;

    particle.externalForces = externalForces;

    ParticleSystem_::Particles.push_back(particle);
}

void ParticleSystem_::UpdateParticles(float deltaTime)
{
    int i = -1;

    for(Particle &particle : Particles)
    {
        i++;

        for(Vector2 force : particle.externalForces)
        {
            particle.vel = Vector2Add(particle.vel, force * deltaTime);
        }

        particle.pos = Vector2Add(particle.pos, particle.vel);

        particle.age += deltaTime;

        if(particle.age > 1)
        {
            Particles.erase(Particles.begin() + i);
        }
    }

    std::cout << i << std::endl;
}

void ParticleSystem_::DrawParticles()
{
    for(Particle particle : Particles)
    {
        DrawCircleV(particle.pos, particle.size, WHITE);
    }
}