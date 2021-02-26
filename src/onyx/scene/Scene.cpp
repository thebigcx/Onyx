#include <onyx/scene/Scene.h>
#include <onyx/scene/GameObject.h>
#include <onyx/renderer/Renderer.h>
#include <onyx/renderer/Font.h>
#include <onyx/scene/Component.h>
#include <onyx/scene/Sprite.h>
#include <onyx/scene/Script.h>

#include <algorithm>

namespace Onyx
{

Scene::Scene(const std::string& name_)
    : name(name_)
{
    
}

void Scene::addGameObject(const std::shared_ptr<GameObject>& object)
{
    m_objects.push_back(object);
}

void Scene::removeGameObject(const std::shared_ptr<GameObject>& object)
{
    m_objects.erase(std::find(m_objects.begin(), m_objects.end(), object));
}

std::shared_ptr<GameObject> Scene::duplicateGameObject(const std::shared_ptr<GameObject>& object)
{
    auto object2 = std::make_shared<GameObject>(object->name);

    object2->m_transform = std::make_shared<Transform>(*object->m_transform);
    
    if (object->hasComponent<Sprite>())
    {
        object2->addComponent(new Sprite(*object->getComponent<Sprite>()));
    }

    addGameObject(object2);

    return object2;
}

std::shared_ptr<GameObject> Scene::findGameObject(const std::string& name) const
{
    for (auto& object : m_objects)
    {
        if (object->name == name)
        {
            return object;
        }
    }

    return nullptr;
}

void Scene::internalUpdate(float dt)
{
    for (auto& object : m_objects)
    {
        if (object)
            object->update(dt);
    }

    update(dt);
}

void Scene::internalRender()
{
    Renderer::start();

    for (auto& object : m_objects)
    {
        if (object)
            object->render();
    }

    Renderer::end();
}

void Scene::internalInit()
{
    m_camera = std::make_shared<Camera>();

    m_font = std::make_shared<Font>("assets/test.ttf", 32);

    init();
}

void Scene::internalDestroy()
{
    for (auto& object : m_objects)
    {
        object->destroy();
    }
}

}