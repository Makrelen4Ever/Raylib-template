#pragma once

//Defines a simple Transform struct
struct MTransform
{
    Vector2 position;

    float Scale;
    float Dir;
};

bool Col(Vector2 v1, Vector2 v1S, Vector2 v2, Vector2 v2S);