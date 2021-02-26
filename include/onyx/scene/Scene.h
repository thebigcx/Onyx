#pragma once

#include <onyx/scene/Camera.h>

#include <memory>
#include <vector>
#include <string>

namespace Onyx
{

class Texture;
class GameObject;
class Font;

class Scene
{
    friend class Game;

public:
    Scene(const std::string& name_);

    virtual ~Scene() {}

    virtual void update(float dt) = 0;
    virtual void init() = 0;

    std::shared_ptr<Camera> getCamera() const { return m_camera; }

    void addGameObject(const std::shared_ptr<GameObject>& object);
    void removeGameObject(const std::shared_ptr<GameObject>& object);
    
    std::shared_ptr<GameObject> duplicateGameObject(const std::shared_ptr<GameObject>& object);

    std::shared_ptr<GameObject> findGameObject(const std::string& name) const;

    std::string name;

private:
    std::shared_ptr<Camera> m_camera;

    std::vector<std::shared_ptr<GameObject>> m_objects;

    std::shared_ptr<Font> m_font;

private:
    void internalUpdate(float dt);
    void internalInit();
    void internalRender();
    void internalDestroy();
};

}