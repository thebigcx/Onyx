#include <onyx/scene/Sprite.h>
#include <onyx/scene/GameObject.h>
#include <onyx/scene/Transform.h>
#include <onyx/renderer/Renderer.h>
#include <onyx/renderer/Texture.h>
#include <onyx/maths/Math.h>

namespace Onyx
{

Sprite::Sprite()
{
    m_color = Vector3f(1, 1, 1);
}

void Sprite::render()
{
    auto transform = object->getTransform();

    if (m_texture)
    {
        Renderer::render(m_texture, transform->translation, transform->scale, m_uv1, m_uv2, m_color, -Math::toRadians(transform->rotation));
    }
    else
    {
        Renderer::render(transform->translation, transform->scale, m_color, -Math::toRadians(transform->rotation));
    }
}

void Sprite::setTexture(const std::shared_ptr<Texture>& texture)
{
    m_texture = texture;

    m_uv1 = Vector2f(0, 0);
    m_uv2 = texture->getSize();
}

void Sprite::setTexCoords(const Vector2f& uv1, const Vector2f& uv2)
{
    m_uv1 = uv1;
    m_uv2 = uv2;
}

}