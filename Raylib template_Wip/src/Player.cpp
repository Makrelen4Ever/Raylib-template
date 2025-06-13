#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "src/Rigidbody.h"
#include "src/GenericStructs.h"
#include "src/InputManager.h"
#include "src/Player.h"

//Draws the player based on the texture
//The texture doesn't work at the moment, so i'm using a sphere for debugging.
void Player::DrawPlayer()
{
    // DrawTextureEx(PlayerTexture, transform.pos, transform.rot, transform.Scale, WHITE);
    DrawCircleV(transform.position, 5, WHITE);
}

//Adds a foce to the player rigidbody based on the Inputmanager
//Updates the rigidbody to apply drag, and other factors.
void Player::Move()
{
    Player::rb.vel = Vector2Add(InputManager::Getaxis(Speed), rb.vel);
    Player::rb.Update();

    Player::transform.position = Vector2Add(transform.position, rb.vel);
}

//Initalizing a new player based on a few input parameters
void Player::InitPlayer(MTransform transform, Rigidbody rb, float Speed)
{
    //Player::PlayerTexture = LoadTexture("src/Textures/Square.png");

    Player::transform = transform;
    Player::rb = rb;

    Player::Speed = Speed;
}

//Adds a new player and initializes it.
Player AddPlayer(Vector2 pos, Vector2 vel, Vector2 GravityDir, float scale, float rotation, float drag, float GravityScale, float Speed, bool UseGravity)
{
    //Defines the player
    Player player;

    //Defines a transform for the player
    MTransform tempPlayerTransform;
    tempPlayerTransform.position = pos;
    tempPlayerTransform.Scale = scale;
    tempPlayerTransform.Dir = rotation;

    //Defines a rigidbody for the player.
    Rigidbody tempPlayerrb;
    tempPlayerrb.Drag = drag;
    tempPlayerrb.vel = vel;
    tempPlayerrb.GravityDir = Vector2Normalize(GravityDir);
    tempPlayerrb.GravityScale = GravityScale;
    tempPlayerrb.UseGravity = UseGravity;

    //Initializes the player.
    player.InitPlayer(tempPlayerTransform, tempPlayerrb, Speed);

    //Returns the player.
    return player;
}