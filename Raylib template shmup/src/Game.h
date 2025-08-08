#pragma once

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "InputManager.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"

extern std::vector<Enemy> Enemies;

void Start();
void Update();
void FixedUpdate(float deltaTime);