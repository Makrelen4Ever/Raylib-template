#pragma once

#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>

#include "InputManager.h"

void Start();
void Update();
void FixedUpdate(float deltaTime);

void GetMouseDirection(Vector2 position, float scale);