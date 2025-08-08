#pragma once

struct Bullet_
{
    Vector2 position;
    Vector2 velocity;
    Vector2 size;

    Rectangle Collider;

    float life;

    bool enemy;
};

void AddBullet(Bullet_ bullet);
void UpdateBullets(float deltaTime);

void DrawBullets();