#pragma once

#include <onyx/scene/Component.h>
#include <onyx/maths/Vector3.h>

#include <memory>

namespace Onyx
{

class Texture;

class Sprite : public Component
{
public:
    void render() override;
    void init() override;
    void update(float dt) override;

    void setTexture(const std::shared_ptr<Texture>& texture);

private:
    std::shared_ptr<Texture> m_texture = nullptr;
    Vector3f m_color;
};

}