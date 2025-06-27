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

#include "level.h"

//Defines a screen struct
struct ScreenStruct
{
    float width = 1920;
    float height = 1080;

    float fixedDeltaTime = 100;
};

//Declaring variables
ScreenStruct screen;

ParticleSystem_ parSystem;

Camera2D camera = { 0 };
Player player;

int levelIndex = 0;

//The fixedUpdate function.
//Gets called 'screen.fixedDeltaTime' times a sec.
void FixedUpdate()
{
    player.Move(1.0f/screen.fixedDeltaTime);
    camera.target = Vector2Lerp(camera.target, { player.transform.position.x, player.transform.position.y}, 1.0f / screen.fixedDeltaTime);

    if(player.isdead || IsKeyDown(KEY_R))
    {
        for(int i = 0; i < 50; i++)
        {
            float dir = GetRandomValue(-15, 15) * RAD2DEG;
            float force = GetRandomValue(-5.0f, -10.0f);

            parSystem.AddParticle(player.transform.position, {sin(dir) * force, cos(dir) * force}, {{0, 9.81f * 4}}, 2);
        }

        player = LoadLevel(levelIndex, 20);
    }
};

//Refular update.
//Gets called once a frame.
void Update()
{
    player.DrawPlayer();
};

//Main function.
int main()
{
    //Inits a window based on the screen struct.
    InitWindow(screen.width, screen.height, "Raylib test");
    // SetTargetFPS(100);
    
    player = LoadLevel(levelIndex, 20);

    //Defines the tick variable for the fixed update.
    float tick = 0;

    //Sets all the necesarry variables for the player camera.
    camera.target = {player.transform.position.x, player.transform.position.y + 20.0f};
    camera.offset = {screen.width / 2, screen.height / 2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    //Loops every frame until the window is closed.
    while(WindowShouldClose() == false)
    {
        for(int i = 0; i < 5; i++)
        {
            float dir = GetRandomValue(-14.99999f, 14.99999f) * RAD2DEG;
            float force = GetRandomValue(-4.99999f, -9.99999f);

            parSystem.AddParticle({0, 0}, {sin(dir) * force, cos(dir) * force}, {{0, 9.81f * 4}}, 2);
        }

        //Updates the tick based on deltatime to check if fixed update should be called.
        tick += GetFrameTime();

        if(tick >= 1.0f/screen.fixedDeltaTime)
        {
            //resets the tick, and calls the fixed update.
            tick = 0;
            
            // FixedUpdate();
            parSystem.UpdateParticles(1.0f / screen.fixedDeltaTime);
        }

        //Clears the background, and write the current Fps in the top-left corner.
        BeginDrawing();
            ClearBackground((Color){50, 50, 50, 255});
            DrawFPS(10, 10);

            BeginMode2D(camera);

                //Calls the update function used to draw things on the screen.
                Update();
                // DrawLevel();

                // DrawRectangleV({player.transform.position.x + 1, player.transform.position.y + player.transform.Scale}, {player.transform.Scale - 2, 5}, player.IsOnGround ? GREEN : RED);

                parSystem.DrawParticles();
            EndMode2D();

        EndDrawing();

        //Loads the next level whenever the player says that it has touched the portal.
        if(player.LevelFinished)
        {
            //Adds one to the level index in order to progress.
            levelIndex++;

            //Loads the level, and resets the player.
            player = LoadLevel(levelIndex, 20);
        }
    }

    //Closes the window, and shut down the program.
    CloseWindow();
    return 0;
}