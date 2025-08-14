#pragma once

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "InputManager.h"

#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

struct ScreenStruct
{
    int width = 960;
    int height = 1080;

    float fixedDeltaTime = 100;
    float timeScale = 1;

    float tick = 0;
};

extern ScreenStruct screen;

extern bool Reset;

void Start();
void Update();
void FixedUpdate(float deltaTime);

extern std::vector<Enemy> Enemies;

Vector2 GetMouseDirection(Vector2 position, float scale);