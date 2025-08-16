#pragma once

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "InputManager.h"
#include "ParticleSystem.h"

struct ScreenStruct
{
    int width = 1920;
    int height = 1080;

    float fixedDeltaTime = 20;
    float timeScale = 2;

    float tick = 0;
};

extern ScreenStruct screen;

void Start();
void Update();
void FixedUpdate(float deltaTime);