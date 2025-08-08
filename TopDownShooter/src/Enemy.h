#pragma once

class Enemy
{
    private:
        int ID;

    public:
        //Transform
        Vector2 Position;
        Vector2 Size;

        //Movement
        Vector2 Velocity;
        float Drag;

        float JumpForce;
        float MoveSpeed;

        //Attacking
        float ChargeDistance;
        float ChargeTime;
        float ChargeTimer;
        float ChargeCooldown;

        bool Charging;
        bool Cooldown;

        //Rendering
        Color color;

        Texture2D Idle;
        Texture2D Right;
        Texture2D Left;

        int dir;

        //Collisions
        Rectangle Collider;

        //Health
        int Health;
        bool IsDead;

        //Enemy type
        bool Melee;

        //Functions
        void Draw();
        void UpdateCollider();
        void Update(float deltaTime, Vector2 Target);
};