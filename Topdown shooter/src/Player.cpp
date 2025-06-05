#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "src/Generics/Rigidbody.h"
#include "src/Generics/GenericStructs.h"
#include "src/Generics/InputManager.h"
#include "src/Player.h"

//Defines a player rigidbody, and transform.
Rigidbody M_rb;
MTransform M_transform;

//Draws the player based on the texture
//The texture doesn't work at the moment, so i'm using a sphere for debugging.
void Player::DrawPlayer()
{
    // DrawTextureEx(PlayerTexture, transform.pos, transform.rot, transform.Scale, WHITE);
    DrawCircleV(transform.pos, 5, WHITE);
}

//Adds a foce to the player rigidbody based on the Inputmanager
//Updates the rigidbody to apply drag, and other factors.
void Player::Move()
{
    Player::rb.vel = Vector2Add(InputManager::Getaxis(Speed), rb.vel);
    M_rb.Update();
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
Player AddPlayer(Vector2 pos, Vector2 vel, float scale, float rotation, float drag, float Speed)
{
    //Defines the player
    Player player;

    //Defines a transform for the player
    MTransform tempPlayerTransform;
    tempPlayerTransform.pos = pos;
    tempPlayerTransform.Scale = scale;
    tempPlayerTransform.rot = rotation;

    //Defines a rigidbody for the player.
    Rigidbody tempPlayerrb;
    tempPlayerrb.Drag = drag;
    tempPlayerrb.vel = vel;

    //Initializes the player.
    player.InitPlayer(tempPlayerTransform, tempPlayerrb, Speed);

    //Returns the player.
    return player;
}