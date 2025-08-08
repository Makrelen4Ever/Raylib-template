#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "Bullet.h"
std::vector<Bullet> Bullets;

#include "Enemy.h"
#include "Game.h"

void AddBullet(Bullet bullet)
{
    Bullets.push_back(bullet);
}

void UpdateBullets(float deltaTime)
{   
    int index = -1;

    for(Bullet &bullet : Bullets)
    {
        index++;

        bullet.Position = Vector2Add(bullet.Position, Vector2Scale(bullet.Velocity, deltaTime));

        for(Enemy &enemy : Enemies)
        {
            if(Vector2Distance(Vector2Add(enemy.Position, Vector2Scale(enemy.Size, 0.5f)), bullet.Position) < 5)
            {
                bullet.LifeTime = 0;
                enemy.Health--;
                if(enemy.Health <= 0)
                {
                    enemy.IsDead = true;
                }
            }
        }

        bullet.LifeTime -= deltaTime;
        if(bullet.LifeTime <= 0)
        {
            Bullets.erase(Bullets.begin() + index);
        }
    }
}