#pragma once

class CharacterController
{
    public:
        GameObject gameObject;

        float MoveSpeed;
        float Drag;
        Vector2 Velocity;

        void Move();
}

std::vector<CharacterController> characterControllers;
void AddCharacterController(GameObject object, float drag, float speed);