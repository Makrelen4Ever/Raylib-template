#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "src/Generics/Rigidbody.h"
#include "src/Generics/GenericStructs.h"
#include "src/Generics/InputManager.h"
#include "src/Player.h"

Rigidbody M_rb;
MTransform M_transform;

void Player::DrawPlayer()
{
    // DrawTextureEx(PlayerTexture, transform.pos, transform.rot, transform.Scale, WHITE);
    DrawCircleV(transform.pos, 5, WHITE);
}

void Player::Move()
{
    Player::rb.vel = Vector2Add(InputManager::Getaxis(Speed), rb.vel);
    M_rb.Update();
}

void Player::InitPlayer(MTransform transform, Rigidbody rb, float Speed)
{
    //Player::PlayerTexture = LoadTexture("src/Textures/Square.png");

    Player::transform = transform;
    Player::rb = rb;

    Player::Speed = Speed;
}

Player AddPlayer(Vector2 pos, Vector2 vel, float scale, float rotation, float drag, float Speed)
{
    Player player;

    MTransform tempPlayerTransform;
    tempPlayerTransform.pos = pos;
    tempPlayerTransform.Scale = scale;
    tempPlayerTransform.rot = rotation;

    Rigidbody tempPlayerrb;
    tempPlayerrb.Drag = drag;
    tempPlayerrb.vel = vel;

    player.InitPlayer(tempPlayerTransform, tempPlayerrb, Speed);

    return player;
}