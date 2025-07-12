#pragma once

#include <raylib.h>

class GameObject
{
    private:
        int privateID;

    public:
        //Transform
        Vector2 position;
        Vector2 Scale;
        float rotation;

        //ID
        std::string name;
        std::string tag;
        bool IsActive;

        //Rendering
        Texture2D texture;

        void InitializeGameObject(Vector2 position, Vector2 scale, float rotation, std::string name, std::string tag, bool isActive);
        void Draw(Texture2D texture, Vector2 position, float rotation, float scale, Color color);
};

class GameObjectManager
{
    public:
        std::vector<GameObject> ObjectList;
        void AddGameObject(Vector2 position, Vector2 scale, float rotation, std::string name, std::string tag, bool isActive, Texture2D texture);
};