#include <raylib.h>
#include <raymath.h>

#define RAYGUI_IMPLEMENTATION
#include <raygui.h>

#include <iostream>
#include <vector>
#include <math.h>
#include <string>

#include "GameObject.h"

struct ScreenStruct
{
    int width = 1920;
    int height = 1080;
};

ScreenStruct screen;

int main()
{
    InitWindow(screen.width, screen.height, "Raylib test");
    SetTargetFPS(120);

    SetExitKey(KEY_ESCAPE);

    Texture2D texture = LoadTexture("src/BombEnemy.png");

    GameObjectManager objectManager;

    objectManager.AddGameObject({screen.width / 2, screen.height/2 - 250}, {.1f, 0}, 0, "Player1", "Player", true, texture);
    objectManager.AddGameObject({screen.width / 2, screen.height/2}, {.2f, 0}, 0, "Player2", "Player", true, texture);
    objectManager.AddGameObject({screen.width / 2, screen.height/2 + 250}, {.3f, 0}, 0, "Player3", "Player", true, texture);

    GameObject selectedObject;
    selectedObject = objectManager.ObjectList[0];
    int selectedIndex = 0;

    while(WindowShouldClose() == false)
    {

        BeginDrawing();
        ClearBackground((Color){50, 50, 50, 255});
        DrawFPS(10, 10);

        GameObject& ObjectInstance = objectManager.ObjectList[selectedIndex];
        ObjectInstance = selectedObject;

        for(int i = 0; i < (int)objectManager.ObjectList.size(); i++)
        {
            GameObject& object = objectManager.ObjectList[i];

            if(GuiButton({50, (float)i * 100 + 50, 500, 100}, object.name.c_str()))
            {
                selectedObject = object;
                selectedIndex = i;
            }

            if(!object.IsActive)
            {
                continue;
            }
            object.Draw(object.texture, object.position, object.rotation, object.Scale.x, WHITE);
        }

        DrawText(selectedObject.name.c_str(), screen.width/2, 100, 50, WHITE);

        if(GuiButton({screen.width - 200, 200, 150, 100}, selectedObject.IsActive ? "Active: true" : "Active: false"))
        {
            selectedObject.IsActive = !selectedObject.IsActive;
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}