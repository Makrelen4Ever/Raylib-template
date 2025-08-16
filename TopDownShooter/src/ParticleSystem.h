#pragma once

class ParticleSystem_ 
{
    public:
        //256b per particle
        struct Particle
        {
            Vector2 pos;
            Vector2 vel;

            int age;
        };

        std::vector<Particle> Particles;

        void AddParticle(Vector2 pos, Vector2 vel);
        void UpdateParticles(float deltaTime);
        void DrawParticles();

        int parCount;
};