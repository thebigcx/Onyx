#include <onyx/scene/Sprite.h>
#include <onyx/scene/GameObject.h>
#include <onyx/scene/Transform.h>
#include <onyx/renderer/Renderer.h>

namespace Onyx
{

void Sprite::render()
{
    auto transform = object->getTransform();
    Renderer::render(m_texture, transform->translation, transform->scale, m_color);
}

void Sprite::init()
{
    m_color = Vector3f(1, 1, 1);
}

void Sprite::update(float dt)
{

}

void Sprite::setTexture(const std::shared_ptr<Texture>& texture)
{
    m_texture = texture;
}

}