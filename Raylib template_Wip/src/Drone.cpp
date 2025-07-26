#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "src/Rigidbody.h" 
#include "src/GenericStructs.h"

#include "Drone.h"
#include "ParticleSystem.h"
#include "Bullet.h"

void Drone::DrawDrone()
{
    Rectangle source = { 0, 0, (float)DroneTexture.width, (float)DroneTexture.height };
    Vector2 origin = { DroneTexture.width * transform.Scale / 2.0f, DroneTexture.height * transform.Scale / 2.0f };
    DrawTexturePro(
        DroneTexture,
        source,
        { transform.position.x + origin.x/2, transform.position.y + origin.y/2, DroneTexture.width * transform.Scale, DroneTexture.height * transform.Scale },
        origin,
        rb.vel.x / 3,
        WHITE
    );
}

void Drone::Move(float fixedDeltaTime, Vector2 Target)
{
    if(Vector2Distance(Target, transform.position) > 150)
    {
        Vector2 velocityDir = Vector2Subtract(Target, transform.position);

        velocityDir = Vector2Normalize(velocityDir);
        velocityDir = Vector2Multiply(velocityDir, {Acceleration.x, Acceleration.y});
        velocityDir = Vector2Add(velocityDir, {0, -200});
        velocityDir = Vector2Scale(velocityDir, fixedDeltaTime);

        Drone::rb.vel = Vector2Add(velocityDir, rb.vel);
    }

    Drone::fireTimer += fixedDeltaTime;
    if(fireTimer > fireRate)
    {
        Vector2 TargetDir = Vector2Subtract(Target, transform.position);

        TargetDir = Vector2Normalize(TargetDir);
        TargetDir = Vector2Scale(TargetDir, 500);

        fireTimer = 0;
        AddBullet(transform.position, TargetDir, 5, true, false, true);
    }

    Drone::rb.vel = Vector2Scale(Drone::rb.vel, rb.Drag);
    Drone::rb.Update(fixedDeltaTime);

    Drone::transform.position = Vector2Add(transform.position, Vector2Scale(rb.vel, fixedDeltaTime));
}

void AddDroneEnemy(Vector2 Position, Vector2 Vel, Vector2 Acceleration, float scale, float Drag, int health, Texture2D texture)
{
    Drone instance;
    MTransform transformInstance;
    Rigidbody rigidbodyInstance;

    transformInstance.position = Position;
    transformInstance.Dir = 0;
    transformInstance.Scale = scale;

    instance.CollisionScale = Vector2Scale({976, 616}, scale);

    rigidbodyInstance.vel = Vel;
    rigidbodyInstance.Drag = Drag;
    rigidbodyInstance.UseGravity = false;
    rigidbodyInstance.GravityDir = {0, 0};
    rigidbodyInstance.GravityScale = 0;

    instance.transform = transformInstance;
    instance.rb = rigidbodyInstance;

    instance.Acceleration = Acceleration;

    instance.fireRate = 3;
    instance.fireTimer = 0;

    instance.health = health;

    instance.DroneTexture = texture;

    drones.push_back(instance);

    return;
}

void UpdateDrones(float deltaTime, Vector2 PlayerPos)
{
    for(Drone &drone : drones)
    {
        drone.Move(deltaTime, PlayerPos);
    }
}

void DrawDrones()
{
    for(Drone drone : drones)
    {
        drone.DrawDrone();
    }
}

int GetDroneLength()
{
    return drones.size();
}

int RemoveDrone(int index)
{
    drones.erase(drones.begin() + index);
    return 1;
}

Drone GetDrone(int index)
{
    return drones[index];
}

void DamageDrone(int index, int Damage)
{
    drones[index].health -= Damage;
}