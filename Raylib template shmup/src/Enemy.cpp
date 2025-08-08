#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "Bullet.h"
#include "Enemy.h"
#include "Game.h"

void Enemy::InitEnemy()
{
    Enemy::TimeAlive = GetTime();
    Enemy::ID = (int)Enemies.size();
}

void Enemy::Update(float deltaTime)
{
    Enemy::velocity = Vector2Add(velocity, {sin(((float)GetTime() - TimeAlive) / 1.0f) * 20.0f, 5});
    Enemy::velocity = Vector2Scale(velocity, Drag);

    Enemy::position = Vector2Add(position, Vector2Scale(velocity, deltaTime));

    Enemy::Collider = {
        position.x,
        position.y,
        size.x,
        size.y,
    };

    Enemy::enemyBullet = {
        position,
        enemyBullet.velocity,
        enemyBullet.size,
        enemyBullet.Collider,
        enemyBullet.life,
        true
    };

    Enemy::fireTick += deltaTime;

    if(fireTick > 1.0f / fireRate)
    {
        AddBullet(enemyBullet);
        Enemy::fireTick = 0;
    }
}

void Enemy::Draw()
{
    DrawRectangleV(position, size, {255, 112, 112, 255});
}