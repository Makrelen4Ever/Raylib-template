#include <raylib.h>
#include <raymath.h>

#include <iostream>
#include <vector>
#include <string>
#include <math.h>

#include "GameObject.h"

void GameObject::InitializeGameObject(Vector2 position, Vector2 scale, float rotation, std::string name, std::string tag, bool isActive)
{
    GameObject::position = position;
    GameObject::Scale = scale;
    GameObject::rotation = rotation;

    GameObject::name = name;
    GameObject::tag = tag;
    GameObject::IsActive = isActive;
}

void GameObject::Draw(Texture2D texture, Vector2 position, float rotation, float scale, Color color)
{
    DrawTextureEx(texture, Vector2Subtract(position, Vector2Scale({texture.width / 2, texture.height / 2}, scale)), rotation, scale, color);
}


void GameObjectManager::AddGameObject(Vector2 position, Vector2 scale, float rotation, std::string name, std::string tag, bool isActive, Texture2D texture)
{
    GameObject objectInstance;
    objectInstance.InitializeGameObject(position, scale, rotation, name, tag, isActive);
    objectInstance.texture = texture;

   GameObjectManager::ObjectList.push_back(objectInstance);
}