#pragma once

class ParticleSystem_ 
{
    private:
        //256b per particle
        struct Particle
        {
            Vector2 pos;
            Vector2 vel;

            float age;
        };

        std::vector<Particle> Particles;

    public:
        void AddParticle(Vector2 pos, Vector2 vel);
        void UpdateParticles(float deltaTime, Vector2 target, float forceMult);
        void DrawParticles();
};