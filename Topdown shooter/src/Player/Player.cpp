#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "Player.h"

struct MTransform M_transform;
struct Rigidbody M_rb;

Rigidbody Player::rb()
{
    return rb;
}

MTransform Player::transform()
{
    return transform;
}

void Player::LoadPlayerTexture()
{
    this->texture = LoadTexture("src/Textures/Square.png");
}

void Player::DrawPlayer()
{
    DrawTextureEx(texture, transform.pos, transform.rot, transform.Scale, WHITE);
}

void Player::Move()
{
    rb.vel = Vector2Add(Vector2Scale(InputManager::Getaxis(Speed), GetFrameTime()), rb.vel);
}

void Player::ApplyDrag()
{
    rb.vel = Vector2Scale(rb.vel, rb.Drag);
}

void Player::Update()
{
    transform.pos = Vector2Add(transform.pos, rb.vel);
}

void InitPlayer(MTransform transform, Rigidbody rb, float Speed)
{
    LoadPlayerTexture();

    this->transform = transform;
    this->rb = rb;

    this->Speed = Speed;
}

Player AddPlayer(Vector2 pos, Vector2 vel, float scale, float rotation, float drag)
{
    Player player;

    MTransform tempPlayerTransform;
    tempPlayerTransform.pos = pos;
    tempPlayerTransform.Scale = scale;
    tempPlayerTransform.rot = rotation;

    Rigidbody tempPlayerrb;
    tempPlayerrb.Drag = .drag;
    tempPlayerrb.vel = vel;

    player.InitPlayer(tempPlayerTransform, tempPlayerrb, 1);

    return player;
}