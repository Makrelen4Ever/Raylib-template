#include <iostream>
#include<raylib.h>

#include "src/GenericStructs.h"

//Defines the MTransform property, based on the Transform header.
MTransform transform;

bool Col(Vector2 v1, Vector2 v1Scale, Vector2 v2, Vector2 v2Scale)
{
    return v1.x + v1Scale.x > v2.x && v1.y + v1Scale.y > v2.y && v1.x < v2.x + v2Scale.x && v1.y < v2.y + v2Scale.y;
};