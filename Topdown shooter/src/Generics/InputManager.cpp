#include <raylib.h>
#include <iostream>

#include "src/Generics/InputManager.h"

//A public static Vector2 that contains the current input.
Vector2 InputManager::Getaxis(float Scale)
{
    //defines X, Y floats to return later.
    float X, Y;

    //Adds and subtracts, based on the left/right input.
    X = IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT) ? -1 : 0;
    X += IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) ? 1 : 0;

    //Adds and subtracts, based on the up/down input.
    Y = IsKeyDown(KEY_W) || IsKeyDown(KEY_UP) ? -1 : 0;
    Y += IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN) ? 1 : 0;

    //Returns the X,Y components scaled with an input variable.
    return {X * Scale, Y * Scale};
}