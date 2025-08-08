#pragma once

class Enemy
{
    private:
        Bullet_ enemyBullet
        {
            {0, 0}, // Position
            {0, 350}, // Velocity
            {15, 15}, // Size

            {50, 50, 50, 50}, //Collider, automatically gets updated at runtime

            5, // Lifetime, decreasing by 1 every second

            true, //Enemy bullet
        };

        float fireRate = 1;
        float fireTick = 0;

        float TimeAlive = 0;

    public:
        Rectangle Collider;

        Vector2 position;
        Vector2 size;

        Vector2 velocity;
        float Drag;

        float MoveSpeed;

        int health;
        bool IsDead = false;

        int ID;

        void InitEnemy();
        void Update(float deltaTime);
        void Draw();
};