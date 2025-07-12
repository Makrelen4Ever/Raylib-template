#pragma once

class ParticleSystem_ 
{
    public:
        //256b per particle
        struct Particle
        {
            Vector2 pos;
            Vector2 vel;

            float age;

            float mass;

            int id;
        };

        std::vector<Particle> Particles;

        void AddParticle(Vector2 pos, Vector2 vel, float mass, int id);
        void UpdateParticles(float deltaTime, Vector2 target, float forceMult, bool calOtherParticles, int screenWidth, int screenHeight);
        void DrawParticles();

        int parCount;
};