#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <math.h>

#include "src/GenericStructs.h"
#include "src/Rigidbody.h"
#include "src/InputManager.h"
#include "src/Player.h"
#include "src/ParticleSystem.h"
#include "src/Bullet.h"
#include "src/Drone.h"

#include "level.h"

//Defines a screen struct
struct ScreenStruct
{
    float width = 1920;
    float height = 1080;

    float fixedDeltaTime = 100;
    float timeScale = 2;
};

//Declaring variables
ScreenStruct screen;

ParticleSystem_ parSystem;

Camera2D camera = { 0 };
Player player;

int levelIndex = 0;

int DroneSpawnRate = 2;
float DroneSpawnTimer = 0;

Texture2D DroneTexture;

//The fixedUpdate function.
//Gets called 'screen.fixedDeltaTime' times a sec.
void FixedUpdate()
{
    player.Move(1.0f/screen.fixedDeltaTime);
    camera.target = Vector2Lerp(camera.target, { player.transform.position.x, player.transform.position.y}, 1.0f / screen.fixedDeltaTime * 3);

    player.FireTimer += 1.0f / screen.fixedDeltaTime;
    player.RocketTimer += 1.0f / screen.fixedDeltaTime;

    //Shoot rocket
    if(player.RocketTimer > player.RocketFireRate && IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
    {
        player.RocketTimer = 0;

        Vector2 mouseWorldPos;
        Vector2 mouseDir;

        mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        mouseDir = Vector2Normalize(Vector2Subtract(mouseWorldPos, player.transform.position));
        //Position, velocity, size, enemy bullet, rocket, gravity
        AddBullet(player.transform.position, Vector2Scale(mouseDir, 500), 10, false, true, false);

        player.rb.vel = Vector2Add(player.rb.vel, Vector2Scale(mouseDir, -1 * 900));
    }

    //Shoot regular bullet
    if(player.FireTimer > player.Firerate && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        player.FireTimer = 0;

        Vector2 mouseWorldPos;
        Vector2 mouseDir;

        mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
        mouseDir = Vector2Normalize(Vector2Subtract(mouseWorldPos, player.transform.position));
        mouseDir = Vector2Rotate(mouseDir, GetRandomValue(-25, 25) / 10 * DEG2RAD);
        //Position, velocity, size, enemy bullet, rocket, gravity
        AddBullet(player.transform.position, Vector2Scale(mouseDir, 1000), 5, false, false, true);

        player.rb.vel = Vector2Add(player.rb.vel, Vector2Scale(mouseDir, -1 * player.Recoil));
    }

    UpdateBullets(1.0f / screen.fixedDeltaTime, player.transform.position, parSystem, player);

    //Spawn drones
    DroneSpawnTimer += 1 / screen.fixedDeltaTime;
    if(DroneSpawnTimer > DroneSpawnRate)
    {
        DroneSpawnTimer = 0;
        //Position, vel, acceleration, scale, drag, health, texture
        AddDroneEnemy(Vector2Add(player.transform.position, {(float)GetRandomValue(-1000, 1000), -500}), {0, 0}, {300, 300}, .05f, .99f, 3, DroneTexture);
    }

    parSystem.UpdateParticles(1.0f / screen.fixedDeltaTime);
    UpdateDrones(1.0f / screen.fixedDeltaTime, player.transform.position);
};

//Refular update.
//Gets called once a frame.
void Update()
{
    player.DrawPlayer();
    DrawBullets();
    DrawDrones();
};

//Main function.
int main()
{
    //Inits a window based on the screen struct.
    InitWindow(screen.width, screen.height, "Raylib test");
    SetTargetFPS(60);
    
    player = LoadLevel(levelIndex, 50);

    //Defines the tick variable for the fixed update.
    float tick = 0;

    //Sets all the necesarry variables for the player camera.
    camera.target = {player.transform.position.x, player.transform.position.y + 20.0f};
    camera.offset = {screen.width / 2, screen.height / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    parSystem.ID = 133;

    DroneTexture = LoadTexture("src/Textures/IRS_Drone.png");

    //Loops every frame until the window is closed.
    while(WindowShouldClose() == false)
    {
        //Updates the tick based on deltatime to check if fixed update should be called.
        tick += GetFrameTime() * screen.timeScale;

        if(tick >= 1.0f/screen.fixedDeltaTime)
        {
            while(tick > 0)
            {
                //resets the tick, and calls the fixed update.
                tick -= GetFrameTime();
                
                FixedUpdate();
            }
        }

        //Clears the background, and write the current Fps in the top-left corner.
        BeginDrawing();
            ClearBackground((Color){50, 50, 50, 255});
            DrawFPS(10, 10);

            BeginMode2D(camera);

                //Calls the update function used to draw things on the screen.
                Update();
                DrawLevel();

                parSystem.DrawParticles();
            EndMode2D();

        EndDrawing();

        //Loads the next level whenever the player says that it has touched the portal.
        if(player.LevelFinished)
        {
            //Adds one to the level index in order to progress.
            levelIndex++;

            //Loads the level, and resets the player.
            player = LoadLevel(levelIndex, 50);
        }
    }

    //Closes the window, and shut down the program.
    CloseWindow();
    return 0;
}