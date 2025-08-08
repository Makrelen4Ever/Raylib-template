#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "InputManager.h"
#include "Bullet.h"
#include "Player.h"

bool ShotLastFrame = false;

void Player::Update(float deltaTime)
{
    Player::velocity = Vector2Add(velocity, InputManager::Getaxis(MoveSpeed));
    Player::velocity = Vector2Scale(velocity, Drag);

    Player::position = Vector2Add(position, Vector2Scale(velocity, deltaTime));

    Player::Collider = {
        position.x,
        position.y,
        size.x,
        size.y,
    };

    Player::playerBullet = {
        position,
        playerBullet.velocity,
        playerBullet.size,
        playerBullet.Collider,
        playerBullet.life,
        false
    };

    if(IsKeyDown(InputManager::Shoot) && !ShotLastFrame)
    {
        AddBullet(playerBullet);
        ShotLastFrame = true;
    }else{
        if(!IsKeyDown(InputManager::Shoot))
        {
            ShotLastFrame = false;
        }else{
            Player::fireTick += deltaTime;

            if(fireTick > 1.0f / FireRate)
            {
                AddBullet(playerBullet);
                Player::fireTick = 0;
            }
        }
    }
}

void Player::Draw()
{
    DrawRectangleV(position, size, WHITE);
}