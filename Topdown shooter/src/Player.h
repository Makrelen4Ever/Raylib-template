# pragma once

class Player
{   
    public:
        MTransform transform;
        Rigidbody rb;

        Texture2D PlayerTexture;

        float Speed;

        void DrawPlayer();

        void Move();

        void InitPlayer(MTransform transform, Rigidbody rb, float Speed);
};

Player AddPlayer(Vector2 pos, Vector2 vel, float scale, float rotation, float drag, float Speed);
