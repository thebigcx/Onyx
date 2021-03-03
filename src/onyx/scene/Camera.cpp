#include <onyx/scene/Camera.h>
#include <onyx/core/Game.h>
#include <onyx/maths/Quaternion.h>
#include <onyx/maths/Math.h>

namespace Onyx
{

Camera::Camera()
{

}

Matrix4f Camera::getProjectionMatrix() const
{
    Vector2u size = Game::getInstance()->getWindow()->getSize();
    return Matrix4f::ortho(0.f, size.x, 0.f, size.y, -1.f, 1.f);
}

Matrix4f Camera::getViewMatrix() const
{
    Vector3f pos(transform.translation.x, transform.translation.y, 1.f);
    Vector3f object(transform.translation.x, transform.translation.y, 0.f);

    Quaternionf upRotation(Vector3f(0, 0, Math::toRadians(transform.rotation)));
    Vector3f up(Quaternionf::rotate(upRotation, Vector3f(0, 1, 0)));

    return Matrix4f::lookAt(pos, object, up);
}

}