#pragma once

#include <onyx/Camera.h>

#include <memory>
#include <vector>

namespace Onyx
{

class Texture;
class GameObject;

class Scene
{
    friend class Game;

public:
    virtual void update(float dt) = 0;
    virtual void init() = 0;

    std::shared_ptr<Camera> getCamera() const { return m_camera; }

protected:
    std::shared_ptr<Camera> m_camera;

    std::vector<std::shared_ptr<GameObject>> m_objects;

    std::shared_ptr<Texture> m_texture;

private:
    void internalUpdate(float dt);
    void internalInit();
    void internalRender();
};

}