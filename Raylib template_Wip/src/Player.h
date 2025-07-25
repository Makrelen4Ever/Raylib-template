# pragma once

//Defines the Player class, and the different functions and variables.
class Player
{   
    public:
        MTransform transform;
        Rigidbody rb;

        Texture2D PlayerTexture;

        float Speed;
        float JumpForce;

        bool IsOnGround;
        bool LevelFinished;
        bool isdead;

        float Firerate = 1;
        float FireTimer = 0;
        float Recoil = 250;

        float RocketFireRate = 5;
        float RocketTimer = 0;

        // bool IsLevelFinished();

        void DrawPlayer();

        void Move(float fixedDeltaTime);

        void InitPlayer(MTransform transform, Rigidbody rb, float Speed, float JumpForce);
};

//Defines the addPlayer function
Player AddPlayer(Vector2 pos, Vector2 vel, Vector2 GravityDir, float scale, float rotation, float drag, float GravityScale, float Speed, float JumpForce, bool UseGravity);