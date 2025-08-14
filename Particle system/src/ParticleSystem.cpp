#include <raylib.h>
#include <raymath.h>
#include <vector>
#include <iostream>
#include <math.h>

#include "ParticleSystem.h"

//Declaring a functino to add particles.
void ParticleSystem_:: AddParticle(Vector2 pos, Vector2 vel, float mass, int id)
{
    Particle particle;

    particle.pos = pos;
    particle.vel = vel;

    particle.mass = mass;

    particle.id = id;

    ParticleSystem_::Particles.push_back(particle);
}

void ParticleSystem_::UpdateParticles(float deltaTime, Vector2 target, float forceMult, bool calOtherParticles, int screenWidth, int screenHeight)
{
    std::vector<Particle> oldParticles = Particles;
    
    //Declaring gravity variables.
    float dx;
    float dy;

    float dist;

    Vector2 normal;


    //Sampling other particles gravity
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
                // dist /= sqrt((dx * dx) + (dy *dy));

                normal = {dx * (1 / dist), dy * (1 / dist)};

                particle.vel.x -= normal.x / dist * otherPar.mass;
                particle.vel.y -= normal.y / dist * otherPar.mass;
            }
        }

        //Sampling target gravity
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

        //Movement
        particle.pos = Vector2Add(particle.pos, Vector2Scale(particle.vel, deltaTime / particle.mass));
    }
}

void ParticleSystem_::DrawParticles()
{
    for(Particle particle : Particles)
    {
        DrawPixelV(particle.pos, BLACK);
    }
}