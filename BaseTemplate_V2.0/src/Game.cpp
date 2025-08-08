#include "Game.h"

void Start()
{

}

void Update()
{
    ClearBackground((Color){50, 50, 50, 255});
    DrawFPS(10, 10);
}

void FixedUpdate(float deltaTime)
{

}

void GetMouseDirection(Vcetor2 position, float scale)
{
    Vector2 mouseDirection;
    mouseDirection = Vector2Subtract(GetMousePosition(), position);
    mouseDirection = Vector2Normalize(mouseDirection);
    mouseDirection = Vector2Scale(mouseDirection, scale);

    return mouseDirection;
}