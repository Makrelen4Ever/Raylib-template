#include <raylib.h>
#include <raymath.h>
#include <iostream>

#include "src/Generics/Rigidbody.h"

//Defines a Rigidbody update loop, based on the Rigidbody header.
void Rigidbody::Update()
{
    //Applies the drag to the current velocity
    Rigidbody::vel = Vector2Scale(vel, Drag);

    //Checks if the the rigidbody should be influenced with gravity. 
    if(UseGravity)
    {
        //Adds gravity based on the direction, abd gravityscale defined in the Rigidbody header file.
        Rigidbody::vel = Vector2Add(vel, Vector2Scale(GravityDir, GravityScale));
    }
}