#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "src/Classes/Player.h"
#include "src/Classes/InputManager.h"

struct MTransform M_transform;
struct Rigidbody M_rb;

void Player::DrawPlayer()
{
    // DrawTextureEx(PlayerTexture, transform.pos, transform.rot, transform.Scale, WHITE);
    DrawCircleV(transform.pos, 5, WHITE);
}

void Player::Move()
{
    Player::rb.vel = Vector2Add(InputManager::Getaxis(Speed), rb.vel);
}

void Player::ApplyDrag()
{
    Player::rb.vel = Vector2Scale(rb.vel, rb.Drag);
}

void Player::Update()
{
    Player::transform.pos = Vector2Add(transform.pos, rb.vel);
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