#pragma once

class Drone
{
    public:
        MTransform transform;
        Vector2 Acceleration;
        Rigidbody rb;

        Texture2D DroneTexture;

        Vector2 CollisionScale;

        float fireRate;
        float fireTimer;

        int health;

        void DrawDrone();
        void Move(float fixedDeltaTime, Vector2 Target);
};

void AddDroneEnemy(Vector2 Position, Vector2 Vel, Vector2 Acceleration, float scale, float Drag, int health, Texture2D texture);
void UpdateDrones(float deltaTime, Vector2 PlayerPos);
void DrawDrones();

static std::vector<Drone> drones;

int GetDroneLength();
int RemoveDrone(int index);
Drone GetDrone(int index);

void DamageDrone(int index, int Damage);