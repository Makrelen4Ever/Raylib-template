#pragma once

#include "Player.h"

struct Bullet
{
    Vector2 pos;
    Vector2 vel;

    Vector2 scale;

    float LifeTime;

    bool Enemy;
    bool Rocket;
    bool gravity;
};

void AddBullet(Vector2 pos, Vector2 vel, float scale, bool enemy, bool rocket, bool gravity);
void UpdateBullets(float deltaTime, Vector2 playerPosition, ParticleSystem_ &parSystem, Player &player);

void DrawBullets();