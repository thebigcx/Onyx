#pragma once

#include <onyx/maths/Vector2.h>
#include <onyx/maths/Matrix4.h>
#include <onyx/scene/Transform.h>

namespace Onyx
{

class Camera
{
public:
    Camera();

    Matrix4f getProjectionMatrix() const;
    Matrix4f getViewMatrix() const;

    Transform transform;
};

}