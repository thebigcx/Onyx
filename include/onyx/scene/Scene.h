#pragma once

#include <onyx/scene/Camera.h>
#include <onyx/core/Core.h>

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

    WeakPtr<GameObject> createGameObject(const std::string& name);
    void removeGameObject(GameObject* object);
    
    WeakPtr<GameObject> duplicateGameObject(const std::shared_ptr<GameObject>& object);

    WeakPtr<GameObject> findGameObject(const std::string& name) const;

    const std::vector<std::shared_ptr<GameObject>>& getObjects() const { return m_objects; }

    std::string name;

private:
    std::shared_ptr<Camera> m_camera;

    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::vector<std::vector<std::shared_ptr<GameObject>>::iterator> m_deleteList;

private:
    void internalUpdate(float dt);
    void internalInit();
    void internalRender();
    void internalDestroy();
};

}