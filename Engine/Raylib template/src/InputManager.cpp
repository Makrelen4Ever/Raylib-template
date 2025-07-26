#include <raylib.h>
#include <raymath.h>

#include <iostream>

#include "InputManager.h"

Vector2 InputManager::axis(float scale)
{
    return Vector2Scale({(IsKeyDown(KEY_D) ? 1 : 0) + (IsKeyDown(KEY_A) ? -1 : 0), (IsKeyDown(KEY_S) ? 1 : 0) + (IsKeyDown(KEY_W) ? -1 : 0)}, scale);
}