#pragma once

class Player
{
    private:
        int ID;

        KeyboardKey DashKey = KEY_SPACE;
    public:
        //Transform
        Vector2 Position;
        Vector2 Size;

        //Movement
        float MoveSpeed;

        Vector2 Velocity;
        float Drag;

        //Dashing
        float DashForce;

        float DashChargeTimer;
        float DashChargeSpeed;
        int DashChargesMax;
        int DashCharges;

        //Collision
        Rectangle Collider;

        //Shooting
        float fireRate;
        float fireRateTimer;

        Bullet playerBullet;

        //Health
        int MaxHealth;
        int CurrHealth;

        //Functions
        void Draw();
        void Update(float deltaTime);
        void UpdateCollider();
};

void InitializePlayer(Player &player);