#pragma once

//Defines a rigidbody with a few parameters.
class Rigidbody
{
    public:
        Vector2 vel;
        float Drag;

        bool UseGravity;
        float GravityScale;

        Vector2 GravityDir;

        void Update(float fixedDeltaTime);
};