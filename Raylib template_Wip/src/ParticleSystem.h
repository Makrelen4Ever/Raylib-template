#pragma once

class ParticleSystem_ 
{
    private:
        struct Particle
        {
            Vector2 pos;
            Vector2 vel;

            std::vector<Vector2> externalForces;

            float size;

            float age;

            Color col;
        };

        std::vector<Particle> Particles;

    public:
        void AddParticle(Vector2 pos, Vector2 vel, std::vector<Vector2> externalForces, float size, Color col);
        void UpdateParticles(float deltaTime);
        void DrawParticles();

        int ID;
        
};