#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "src/Generics/Rigidbody.h"

void Rigidbody::Update()
{
    Rigidbody::vel = Vector2Scale(vel, Drag);

    if(UseGravity)
    {
        Rigidbody::vel = Vector2Add(vel, Vector2Scale(GravityDir, GravityScale));
    }
}