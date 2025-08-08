#pragma once

class Player
{
    private:
        Bullet_ playerBullet = {
            {0, 0}, // Position
            {0, -1500}, // Velocity
            {10, 10}, // Size

            {0, 0, 0, 0}, //Collider, automatically gets updated at runtime

            5, // Lifetime, decreasing by 1 every second

            false, //Enemy bullet
        };

        float FireRate = 2;
        float fireTick = 0;

    public:
        Rectangle Collider;

        Vector2 position;
        Vector2 size;

        Vector2 velocity;
        float Drag;

        float MoveSpeed;

        void Update(float deltaTime);
        void Draw();
};