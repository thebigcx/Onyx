#pragma once

#include <onyx/scene/Component.h>
#include <onyx/maths/Vector2.h>
#include <onyx/maths/Vector3.h>

#include <memory>

namespace Onyx
{

class Texture;

class Sprite : public Component
{
public:
    Sprite();

    void render() override;

    void setTexture(const std::shared_ptr<Texture>& texture);
    void setTexCoords(const Vector2f& uv1, const Vector2f& uv2);

private:
    std::shared_ptr<Texture> m_texture = nullptr;
    Vector3f m_color;

    Vector2f m_uv1;
    Vector2f m_uv2;
};

}