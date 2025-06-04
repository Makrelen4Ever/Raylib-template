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
    private:
        Texture2D texture;

    public:
        MTransform transform;
        Rigidbody rb;

        float Speed;

        void LoadPlayerTexture();

        void DrawPlayer();

        void Move();

        void ApplyDrag();

        void Update();

        void InitPlayer(MTransform transform, Rigidbody rb, float Speed);
};

Player AddPlayer(Vector2 pos, Vector2 vel, float scale, float rotation, float drag);
