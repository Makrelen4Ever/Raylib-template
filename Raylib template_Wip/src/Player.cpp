#include <raylib.h>
#include <raymath.h>
#include <iostream>
#include <vector>

#include "src/Rigidbody.h"
#include "src/GenericStructs.h"
#include "src/InputManager.h"
#include "src/Player.h"
#include "src/Level.h"

//Draws the player based on the texture
//The texture doesn't work at the moment, so i'm using a sphere for debugging.
void Player::DrawPlayer()
{
    // DrawTextureEx(PlayerTexture, transform.pos, transform.rot, transform.Scale, WHITE);
    DrawRectangleV(transform.position, {transform.Scale, transform.Scale}, WHITE);
}

//Adds a foce to the player rigidbody based on the Inputmanager
//Updates the rigidbody to apply drag, and other factors.
void Player::Move(float fixedDeltaTime)
{
    Player::isdead = false;

    Vector2 OldPos = transform.position;

    if(IsOnGround & (InputManager::Getaxis(1).y < 0))
    {
        Player::rb.vel = {rb.vel.x, -JumpForce};
        std::cout << "Jump" << std::endl;
    }

    Player::rb.vel = Vector2Add((Vector2){InputManager::Getaxis(Speed).x, 0}, rb.vel);
    Player::rb.Update(fixedDeltaTime);

    Player::transform.position = Vector2Add(transform.position, Vector2Scale(rb.vel, fixedDeltaTime));

    Player::IsOnGround = false;

    for(int i = 0; i < GetBlocksLength(); i++)
    {
        Block block = GetBlock(i);

        if(Col(transform.position, {transform.Scale, transform.Scale}, {(float)block.x, (float)block.y}, {(float)block.w, (float)block.h}))
        {
            if(block.IsPortal)
            {
                Player::LevelFinished = true;
                continue;
            }

            if(block.IsDangerous)
            {
                Player::isdead = true;
                continue;
            }

            if(abs(OldPos.y - transform.position.y) < 5.0f * rb.GravityScale)
            {
                Player::rb.vel.y = 0;
                Player::transform.position.y = OldPos.y;
            }else
            {
                Player::rb.vel.x = 0;
                Player::transform.position.x = OldPos.x;

                continue;
            }

            if(Col(transform.position, {transform.Scale, transform.Scale}, {(float)block.x, (float)block.y}, {(float)block.w, (float)block.h}))
            {
                Player::rb.vel.x = 0;
                Player::transform.position.x = OldPos.x;
            }
        }

        if(Col({transform.position.x + 1, transform.position.y + transform.Scale}, {transform.Scale - 2, 5}, {(float)block.x, (float)block.y}, {(float)block.w, (float)block.h}))
        {
            Player::IsOnGround = true;
        }
    }

    if(transform.position.y >= 500)
    {
        Player::isdead = true;
    }
}

//Initalizing a new player based on a few input parameters
void Player::InitPlayer(MTransform transform, Rigidbody rb, float Speed, float JumpForce)
{
    //Player::PlayerTexture = LoadTexture("src/Textures/Square.png");

    Player::transform = transform;
    Player::rb = rb;

    Player::Speed = Speed;
    Player::JumpForce = JumpForce;

    Player::LevelFinished = false;
}

//Adds a new player and initializes it.
Player AddPlayer(Vector2 pos, Vector2 vel, Vector2 GravityDir, float scale, float rotation, float drag, float GravityScale, float Speed, float JumpForce, bool UseGravity)
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
    player.InitPlayer(tempPlayerTransform, tempPlayerrb, Speed, JumpForce);

    //Returns the player.
    return player;
}