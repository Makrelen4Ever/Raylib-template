#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "ParticleSystem.h"

void ParticleSystem_::AddParticle(Vector2 Position, Vector2 Velocity, Vector2 Forces)
{
    ParticleSystem_::localParticle.Position = Position;
    ParticleSystem_::localParticle.Forces = Forces;
    ParticleSystem_::localParticle.Velocity = Velocity;
    ParticleSystem_::localParticle.ID = (int)Particles.size();
    ParticleSystem_::Particles.push_back(localParticle);
}

void ParticleSystem_::UpdateParticles(float deltaTime, float SelfAttractionForce, float CenterAttractionForce)
{
    float dx;
    float dy;

    float dist;
    Vector2 normal;

    int particlesIndex = -1;

    for(Particle &particle : Particles)
    {   
        particlesIndex++;

        for(Particle otherPar : Particles)
        {
            if(otherPar.ID == particle.ID)
            {
                continue;
            }

            dx = particle.Position.x - otherPar.Position.x;
            dy = particle.Position.y - otherPar.Position.y;

            dist = sqrt((dx * dx) + (dy * dy));
            dist = fmax(dist, .5f);

            // dist = pow(dist, 2);
            // dist /= sqrt((dx * dx) + (dy *dy));

            normal = {dx * (1 / dist), dy * (1 / dist)};

            particle.Velocity.x -= (normal.x / dist) * deltaTime * SelfAttractionForce;
            particle.Velocity.y -= (normal.y / dist) * deltaTime * SelfAttractionForce;
        }

        dx = particle.Position.x - GetScreenWidth() / 2;
        dy = particle.Position.y - GetScreenHeight() / 2;

        dist = sqrt((dx * dx) + (dy * dy));
        dist = fmax(dist, .5f);

        normal = {dx * (1 / dist), dy * (1 / dist)};

        particle.Velocity.x -= (normal.x / dist) * deltaTime * CenterAttractionForce;
        particle.Velocity.y -= (normal.y / dist) * deltaTime * CenterAttractionForce;

        particle.Position = Vector2Add(particle.Position, Vector2Scale(particle.Velocity, deltaTime));

        particle.Age -= deltaTime;
        if(particle.Age <= 0)
        {
            Particles.erase(Particles.begin() + particlesIndex);
        }
    }
}

void ParticleSystem_::DrawParticles()
{
    for(Particle par : Particles)
    {
        DrawPixelV(par.Position, BLACK);
    }
}

void ParticleSystem_::ReloadParticle(Particle particle)
{
    ParticleSystem_::localParticle = particle;
}