#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "Bullet.h"
#include "Game.h"

std::vector<Bullet_> bullets;

void AddBullet(Bullet_ bullet)
{
    bullets.push_back(bullet);
}

void UpdateBullets(float deltaTime)
{
    int index = -1;

    for(Bullet_ &bullet : bullets)
    {
        index++;

        bullet.position = Vector2Add(bullet.position, Vector2Scale(bullet.velocity, deltaTime));

        bullet.Collider = {
            bullet.position.x,
            bullet.position.y,

            bullet.size.x,
            bullet.size.y,
        };

        if(!bullet.enemy && Enemies.size() > 0)
        {
            int enemyIndex = -1;

            for(Enemy &enemy : Enemies)
            {
                enemyIndex++;

                if(CheckCollisionRecs(enemy.Collider, bullet.Collider))
                {
                    std::cout << "Hit" << std::endl;

                    bullet.life = 0;
                    enemy.health--;

                    if(enemy.health <= 0)
                    {
                        Enemies.erase(Enemies.begin() + enemyIndex);
                    }

                    break;
                }
            }
        }

        bullet.life -= deltaTime;
        if(bullet.life <= 0)
        {
            bullets.erase(bullets.begin() - index);
        }
    }
}

void DrawBullets()
{
    for(Bullet_ bullet : bullets)
    {
        DrawRectangleV(Vector2Add(bullet.position, {5, 5}), bullet.size, {27,29,97,255});
        DrawRectangleV(bullet.position, bullet.size, bullet.enemy ? (Color){255, 112, 112, 255} : WHITE);
    }
}