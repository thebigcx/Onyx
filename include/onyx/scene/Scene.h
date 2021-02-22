#pragma once

#include <onyx/scene/Camera.h>

#include <memory>
#include <vector>
#include <string>

namespace Onyx
{

class Texture;
class GameObject;

class Scene
{
    friend class Game;

public:
    Scene(const std::string& name_);

    virtual ~Scene() {}

    virtual void update(float dt) = 0;
    virtual void init() = 0;

    std::shared_ptr<Camera> getCamera() const { return m_camera; }

    std::string name;

protected:
    std::shared_ptr<Camera> m_camera;

    std::vector<std::shared_ptr<GameObject>> m_objects;

private:
    void internalUpdate(float dt);
    void internalInit();
    void internalRender();
};

}