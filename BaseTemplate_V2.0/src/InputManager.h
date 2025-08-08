# pragma once

//Defines the InputManager class
//Defines the Getaxis vector from the inputmanager.
class InputManager 
{
    public:
        static Vector2 Getaxis(float Scale);

        static const KeyboardKey Shoot = KEY_X;
        static const KeyboardKey Dash = KEY_Z;
        static const KeyboardKey Special = KEY_C;
};