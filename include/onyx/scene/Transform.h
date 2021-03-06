#pragma once

#include <onyx/maths/Vector2.h>

namespace Onyx
{

class Transform
{
public:
    Vector2f translation;
    float rotation = 0;
    Vector2f scale;
};

}