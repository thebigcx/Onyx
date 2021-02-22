#pragma once

#include <onyx/maths/Vector2.h>

namespace Onyx
{

class Keyboard
{
public:
    static bool isKeyPressed(int key);
};

class Mouse
{
public:
    static bool isMousePressed(int button);

    static Vector2u getMousePosition();
};

}