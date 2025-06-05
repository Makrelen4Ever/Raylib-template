# pragma once

struct MTransform
{
    Vector2 pos;

    float Scale;
    float rot;
};

struct Rigidbody
{
    Vector2 vel;

    float Drag;
};

class Player
{   
    public:
        MTransform transform;
        Rigidbody rb;

        Texture2D PlayerTexture;

        float Speed;

        void DrawPlayer();

        void SetPlayerTexture();

        void Move();

        void ApplyDrag();

        void Update();

        void InitPlayer(MTransform transform, Rigidbody rb, float Speed);
};

Player AddPlayer(Vector2 pos, Vector2 vel, float scale, float rotation, float drag, float Speed);
