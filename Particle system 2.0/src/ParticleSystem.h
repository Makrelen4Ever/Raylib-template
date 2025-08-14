#pragma once

struct Particle 
{
    Vector2 Position;
    Vector2 Velocity;
    Vector2 Forces;

    int Age;
    int ID;
};

class ParticleSystem_ {
    private:
        int ID;

    public:
        Particle localParticle;

        void UpdateParticles(float deltaTime, float SelfAttractionForce, float CenterAttractionForce);
        void DrawParticles();
        void ReloadParticle(Particle particle);
        void AddParticle(Vector2 Position, Vector2 Velocity, Vector2 Forces);

        std::vector<Particle> Particles;
};