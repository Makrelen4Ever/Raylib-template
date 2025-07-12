#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
#include <math.h>

#include "ParticleSystem.h"

//particles
void ParticleSystem_:: AddParticle(Vector2 pos, Vector2 vel, float mass, int id)
{
    Particle particle;

    particle.pos = pos;
    particle.vel = vel;

    particle.age = 0;
    particle.mass = mass;

    particle.id = id;

    ParticleSystem_::Particles.push_back(particle);
}

void ParticleSystem_::UpdateParticles(float deltaTime, Vector2 target, float forceMult, bool calOtherParticles, int screenWidth, int screenHeight)
{
    std::vector<Particle> oldParticles = Particles;
    
    //Gravity simulation
    float dx;
    float dy;

    float dist;

    Vector2 normal;

    parCount = -1;
    for(Particle &particle : Particles)
    {
        parCount++;
        
        if(calOtherParticles)
        {
            for(auto otherPar : oldParticles)
            {
                if(otherPar.id == particle.id)
                {
                    continue;
                }

                dx = particle.pos.x - otherPar.pos.x;
                dy = particle.pos.y - otherPar.pos.y;

                dist = sqrt((dx * dx) + (dy * dy));
                dist = fmax(dist, .5f);

                dist = pow(dist, 2);
                dist /= sqrt((dx * dx) + (dy *dy));

                normal = {dx * (1 / dist), dy * (1 / dist)};

                particle.vel.x -= normal.x / dist * otherPar.mass;
                particle.vel.y -= normal.y / dist * otherPar.mass;
            }
        }

        dx = particle.pos.x - target.x;
        dy = particle.pos.y - target.y;

        dist = sqrt((dx * dx) + (dy * dy));
        dist = fmax(dist, .5f);

        dist = pow(dist, 2) / 2;
        dist /= sqrt((dx * dx) + (dy *dy));

        normal = {dx * (1 / dist), dy * (1 / dist)};

        particle.vel.x -= normal.x / dist * forceMult;
        particle.vel.y -= normal.y / dist * forceMult;

        particle.vel = Vector2Scale(particle.vel, 0.99f);
        particle.vel.y += 9.81f;

        //Movement
        particle.pos = Vector2Add(particle.pos, Vector2Scale(particle.vel, deltaTime / particle.mass));

        // if(dist < 5)
        // {
        //     particle.pos = {GetRandomValue(0, screenWidth), GetRandomValue(0, screenHeight)};
        //     particle.pos = Vector2Scale(particle.pos, 2);
        //     particle.pos = Vector2Add(particle.pos, {-screenWidth, -screenHeight});
        // }

        //Aging
        particle.age += deltaTime;

        if(particle.age > 5)
        {
            Particles.erase(Particles.begin() + parCount);
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