#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "InputManager.h"
#include "Rigidbody.h"
#include "GenericStructs.h"
#include "Player.h"
#include "Level.h"
#include "Drone.h"
#include "ParticleSystem.h"
#include "Bullet.h"

std::vector<Bullet> bullets;

void AddBullet(Vector2 pos, Vector2 vel, float scale, bool enemy, bool rocket, bool gravity)
{
    Bullet instance;

    instance.pos = pos;
    instance.vel = vel;

    instance.scale = {scale, scale};

    instance.LifeTime = 0;

    instance.Enemy = enemy;
    instance.Rocket = rocket;
    instance.gravity = gravity;

    bullets.push_back(instance);
}

void UpdateBullets(float deltaTime, Vector2 playerPosition, ParticleSystem_ &parSystem, Player &player)
{
    int i = -1;

    for(Bullet &bullet : bullets)
    {   
        i++;

        if(bullet.gravity){
            bullet.vel = Vector2Add(bullet.vel, {0, 5});
        }

        bullet.pos = Vector2Add(bullet.pos, Vector2Scale(bullet.vel, deltaTime));

        if(bullet.LifeTime > .01f)
        {
            for(int i = 0; i < GetBlocksLength(); i++)
            {
                Block block = GetBlock(i);

                if(Vector2Distance(bullet.pos, {(float)block.x, (float)block.y}) > block.w * 2)
                {
                    continue;;
                }

                if(Col(bullet.pos, bullet.scale, {(float)block.x, (float)block.y}, {(float)block.w, (float)block.h}))
                {
                    bullet.LifeTime = INFINITY;
                }
            }
        }

        if(!bullet.Enemy)
        {
            for(int j = 0; j < GetDroneLength(); j++)
            {
                Drone drone = GetDrone(j);

                if(Col(bullet.pos, bullet.scale, drone.transform.position, drone.CollisionScale))
                {
                    for(int k = 0; k < 20; k++)
                    {
                        float dir = GetRandomValue(-360, 360) * DEG2RAD;
                        float force = GetRandomValue(-5.0f, -10.0f);

                        parSystem.AddParticle(drone.transform.position, {sin(dir) * force, cos(dir) * force}, {{0, 9.81f * 4}}, 2, RED);
                    }

                    if(!bullet.Rocket){
                        bullet.LifeTime += INFINITY;
                    }

                    DamageDrone(j, 1);
                    if(drone.health < 1)
                    {
                        RemoveDrone(j);
                    }
                }
            }
        }

        bullet.LifeTime += deltaTime;
        if(bullet.LifeTime > 10 || Vector2Distance(bullet.pos, playerPosition) > 2000)
        {
            bullets.erase(bullets.begin() + i);
        }
    }
}

void DrawBullets()
{
    for(auto bullet : bullets)
    {
        DrawRectangleV(bullet.pos, bullet.scale, ORANGE);
    }
}
