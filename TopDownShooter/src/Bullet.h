#pragma once

struct Bullet
{   
    Vector2 Position;
    Vector2 Velocity;

    float LifeTime;
    bool Enemy;
};

extern std::vector<Bullet> Bullets;

void AddBullet(Bullet bullet);
void UpdateBullets(float deltaTime);