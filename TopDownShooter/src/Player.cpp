#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "InputManager.h"

#include "Game.h"
#include "Bullet.h"
#include "Player.h"

void Player::Draw()
{
    DrawRectangleV(Position, Size, WHITE);
    for(int i = 0; i < DashCharges; i++)
    {
        DrawRectangleV({Position.x + Size.x * 1.1f, Position.y + (Size.y * 0.5f * i)}, {Size.y * 0.3f, Size.y * 0.3f}, WHITE);
    }

    DrawRectangle(100, GetScreenHeight() - 25, GetScreenWidth() - 200, 50, {150, 0, 0, 255});
    float HealthRatio = ((float)CurrHealth / (float)MaxHealth);
    DrawRectangle(GetScreenWidth() / 2 - ((GetScreenWidth() / 2 - 100) * HealthRatio), GetScreenHeight() - 25, HealthRatio * (GetScreenWidth() - 200), 50, RED);
}

void Player::UpdateCollider()
{
    Player::Collider = {
        Position.x,
        Position.y,

        Size.x,
        Size.y,
    };
}

bool DashedLastFrame = false;

void Player::Update(float deltaTime)
{
    //Movement
    Vector2 force;

    force = InputManager::Getaxis(MoveSpeed);
    force = Vector2Scale(force, deltaTime);

    Player::Velocity = Vector2Add(force, Velocity);
    Player::Velocity = Vector2Scale(Velocity, Drag * deltaTime);
    Player::Position = Vector2Add(Position, Vector2Scale(Velocity, deltaTime));

    if(Position.x < 0 || Position.x + Size.x > GetScreenWidth())
    {
        Player::Velocity.x *= -1;
        Player::Position.x += Velocity.x * deltaTime;
    }

    if(Position.y < 0 || Position.y + Size.y > GetScreenHeight())
    {
        Player::Velocity.y *= -1;
        Player::Position.y += Velocity.y * deltaTime;
    }

    //Dashing
    Player::DashChargeTimer += deltaTime;
    if(DashChargeTimer >= DashChargeSpeed)
    {
        Player::DashChargeTimer = 0;

        Player::DashCharges++;
        Player::DashCharges = Clamp(DashCharges, 0, DashChargesMax);
    }

    if(DashCharges > 0 && IsKeyDown(DashKey) && !DashedLastFrame)
    {
        Player::DashCharges--;
        DashedLastFrame = true;
        Player::Velocity = InputManager::Getaxis(DashForce);

        Player::DashChargeTimer = 0;
    }else
    {
        if(!IsKeyDown(DashKey))
        {
            DashedLastFrame = false;
        }
    }

    //Shooting
    Player::fireRateTimer += deltaTime;
    if(fireRateTimer > 1.0f / fireRate && IsMouseButtonDown(MOUSE_BUTTON_LEFT))
    {
        fireRateTimer = 0;
        Player::playerBullet.Position = Position;

        Vector2 mouseDirection;

        mouseDirection = GetMouseDirection(Position, 1000);

        Player::Velocity = Vector2Scale(mouseDirection, -5);

        mouseDirection = Vector2Rotate(mouseDirection, -5 * DEG2RAD);

        for(int i = 0; i < 10; i++)
        {
            mouseDirection = Vector2Rotate(mouseDirection, 1 * DEG2RAD);
            Player::playerBullet.Velocity = mouseDirection;
            AddBullet(playerBullet);
        }
    }

    //Enemy collision
    for(Enemy &enemy : Enemies)
    {
        if(CheckCollisionRecs({enemy.Position.x, enemy.Position.y, enemy.Size.x, enemy.Size.x}, {Position.x, Position.y, Size.x, Size.x}))
        {
            Player::CurrHealth -= 10;
            enemy.Velocity = Vector2Scale(Vector2Normalize(Vector2Subtract(enemy.Position, Position)), 500);
        }
    }
}

void InitializePlayer(Player &player)
{
    //Player
    player.Position = {(float)GetScreenWidth() / 2, (float)GetScreenHeight() / 2};
    player.Size = {10, 15};
    player.Velocity = {0, 0};
    player.Drag = 95;
    player.MoveSpeed = 1500;

    player.DashCharges = 2;
    player.DashChargesMax = 2;
    player.DashChargeSpeed = 1;
    player.DashChargeTimer = 0;

    player.DashForce = 1500;

    player.fireRate = 0.5f;
    player.fireRateTimer = 0;

    player.playerBullet = (Bullet){
        player.Position,
        {0, 0},
        5,
        false,
    };

    player.MaxHealth = 100;
    player.CurrHealth = 100;
}