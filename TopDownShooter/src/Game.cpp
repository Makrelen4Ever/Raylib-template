#include "Game.h"
ScreenStruct screen;

bool Reset;

//Declare variables
Player player;
std::vector<Enemy> Enemies;

void Start()
{
    InitializePlayer(player);
    //Enemy
    Enemy enemy;

    enemy.Size = {10, 15};
    enemy.Velocity = {0, 0};
    enemy.Drag = 90;
    enemy.JumpForce = 100000;
    enemy.MoveSpeed = 2500;

    enemy.ChargeTime = .5f;
    enemy.ChargeTimer = 0;
    enemy.ChargeCooldown = 2.5f;
    enemy.ChargeDistance = 200;
    enemy.Charging = false;
    enemy.Cooldown = false;

    enemy.color = RED;

    enemy.Right = LoadTexture("src/Textures/Box_Right.png");
    enemy.Left = LoadTexture("src/Textures/Box_left.png");
    enemy.Idle = LoadTexture("src/Textures/Box_idle.png");

    enemy.Health = 3;
    enemy.IsDead = false;

    enemy.Melee = true;

    Enemies.clear();

    //Spawning enemies
    float direction, radius;

    for(int i = 0; i < 10; i++)
    {
        direction = GetRandomValue(0, 3600) / 10 * DEG2RAD;
        radius = GetRandomValue(0, (float)GetScreenWidth() * 10) / 10;
        enemy.Position = {sin(direction) * radius + GetScreenWidth() / 2, cos(direction) * radius + GetScreenHeight() / 2};

        Enemies.push_back(enemy);
    }
}

void Update()
{
    ClearBackground((Color){50, 50, 50, 255});
    DrawFPS(10, 10);

    player.Draw();
    for(Enemy &enemy : Enemies)
    {
        enemy.Draw();
    }
    for(Bullet bullet : Bullets)
    {
        DrawCircleV(bullet.Position, 5, WHITE);
    }
}

int enemyIndex;

void FixedUpdate(float deltaTime)
{
    player.Update(deltaTime);

    enemyIndex = -1;

    for(Enemy &enemy : Enemies)
    {
        enemyIndex++;

        enemy.Update(deltaTime, Vector2Add(player.Position, Vector2Scale(player.Velocity, deltaTime)));
        if(enemy.IsDead)
        {
            Enemies.erase(Enemies.begin() + enemyIndex);
        }
    }

    UpdateBullets(deltaTime);
}

Vector2 GetMouseDirection(Vector2 position, float scale)
{
    Vector2 mouseDirection;
    mouseDirection = Vector2Subtract(GetMousePosition(), position);
    mouseDirection = Vector2Normalize(mouseDirection);
    mouseDirection = Vector2Scale(mouseDirection, scale);

    return mouseDirection;
}