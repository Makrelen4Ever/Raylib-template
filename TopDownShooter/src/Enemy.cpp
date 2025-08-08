#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "Enemy.h"

void Enemy::Draw()
{
    switch (dir)
    {
        case 1:
            DrawTextureEx(Right, Position, 0, Size.y / 128, color);
            break;

        case -1:
            DrawTextureEx(Left, Position, 0, Size.y / 128, color);
            break;
        
        default:
            DrawTextureEx(Idle, Position, 0, Size.y / 128, color);
            break;
    }
}

void Enemy::Update(float deltaTime, Vector2 Target)
{   
    Enemy::Drag = Cooldown ? 98 : 90;
    Enemy::dir = Velocity.x > 10 ? 1 : Velocity.x < -10 ? -1 : 0;

    Enemy::Velocity = Vector2Scale(Velocity, Drag * deltaTime);
    Enemy::Position = Vector2Add(Position, Vector2Scale(Velocity, deltaTime));

    if(!Melee) return;

    if(Cooldown)
    {
        Enemy::Velocity = Vector2Scale(Velocity, Drag * deltaTime);
        Enemy::Position = Vector2Add(Position, Vector2Scale(Velocity, deltaTime));

        Enemy::ChargeTimer += deltaTime;
        if(ChargeTimer >= ChargeCooldown)
        {
            Enemy::Cooldown = false;
            Enemy::ChargeTimer = 0;
        }

        return;
    }

    if(Vector2Distance(Position, Target) < ChargeDistance)
    {
        Charging = true;
    }

    if(!Charging)
    {
        Vector2 dir = Vector2Subtract(Target, Position);
        dir = Vector2Normalize(dir);
        dir = Vector2Scale(dir, MoveSpeed);
        dir = Vector2Scale(dir, deltaTime);

        Enemy::Velocity = Vector2Add(dir, Velocity);
    }else
    {
        Enemy::color = WHITE;

        Enemy::ChargeTimer += deltaTime;
        if(ChargeTimer > ChargeTime)
        {
            Enemy::color = RED;
            Enemy::ChargeTimer = 0;
            Enemy::Charging = false;
            Cooldown = true;

            Vector2 dir = Vector2Subtract(Target, Position);
            dir = Vector2Normalize(dir);
            dir = Vector2Scale(dir, JumpForce);
            dir = Vector2Scale(dir, deltaTime);

            Enemy::Velocity = dir;
        }
    }
}