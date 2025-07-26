#include <raylib.h>
#include <raymath.h>

#include <vector>
#include <iostream>

#include "GameObject.h"
#include "CharacterController.h"

#include "InputManager.h"

void CharacterController::Move()
{
    if(!gameObject.IsActive)
    {
        return;
    }

    CharacterController::Velocity = Vector2Add(InputManager::axis(MoveSpeed), Velocity);
    CharacterController::Velocity = Vector2Scale(Velocity, Drag);
    CharacterController::gameObject.position = Vector2Add(Velocity, gameObject.position);
}

void AddCharacterController(GameObject object, float drag, float speed)
{
    CharacterController controller;

    controller.gameObject = object;
    controller.Drag = drag;
    controller.MoveSpeed = speed;

    characterControllers.push_back(controller);
}