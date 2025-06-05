#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "src/Classes/InputManager.h"

Vector2 InputManager::Getaxis(float Scale)
{
    float X, Y;

    X = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ? -1 : 0;
    X += IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ? 1 : 0;

    Y = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ? -1 : 0;
    Y += IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ? 1 : 0;
    
    return {X * Scale, Y * Scale};
}