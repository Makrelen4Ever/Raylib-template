#include "Game.h"

std::vector<Enemy> Enemies;

class EnemySpawner
{
    public:
        float EnemySpawnRate = 0.5f;
        float EnemySpawnTick = 0;

        void SpawnEnemies(Enemy enemy, float deltaTime)
        {
            EnemySpawnTick += deltaTime;

            if(EnemySpawnTick > 1 / EnemySpawnRate)
            {
                EnemySpawnTick = 0;
                enemy.InitEnemy();
                Enemies.push_back(enemy);
            }
        }
};

EnemySpawner enemySpawner;
Enemy enemyPreset;

Player player;

void Start()
{
    //Player setup
    player.position = {(float)GetScreenWidth() / 2.0f, (float)GetScreenHeight() / 2.0f};
    player.velocity = {0, 0};
    player.size = {10, 10};

    player.Drag = 0.9f;

    player.MoveSpeed = 35;

    //Enemy
    enemyPreset.position = {170, -50};
    enemyPreset.velocity = {0, 0};
    enemyPreset.size = {30, 30};

    enemyPreset.MoveSpeed = .1f;
    enemyPreset.Drag = 0.95f;

    enemyPreset.health = 3;

    Enemies.push_back(enemyPreset);
}

void Update()
{
    ClearBackground((Color){85, 219, 105, 255}); // Shadow: {27,29,97,255} Enemy: {255, 112, 112, 255} Background: {85, 219, 105, 255}
    DrawFPS(10, 10);

    DrawBullets();
    player.Draw();

    for(Enemy enemy : Enemies)
    {
        enemy.Draw();
        if(enemy.IsDead)
        {
            Enemies.erase(Enemies.begin() + enemy.ID);
        }
    }
}

void FixedUpdate(float deltaTime)
{
    enemySpawner.SpawnEnemies(enemyPreset, deltaTime);

    player.Update(deltaTime);
    UpdateBullets(deltaTime);

    for(Enemy &enemy : Enemies)
    {
        enemy.Update(deltaTime);
    }
}