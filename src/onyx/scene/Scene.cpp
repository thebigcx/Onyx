#include <onyx/scene/Scene.h>
#include <onyx/scene/GameObject.h>
#include <onyx/renderer/Renderer.h>
#include <onyx/renderer/Font.h>
#include <onyx/scene/Component.h>
#include <onyx/scene/Sprite.h>

#include <algorithm>

namespace Onyx
{

Scene::Scene(const std::string& name_)
    : name(name_)
{
    
}

WeakPtr<GameObject> Scene::createGameObject(const std::string& name)
{
    auto object = std::make_shared<GameObject>(name);
    m_objects.push_back(object);
    return object;
}

void Scene::removeGameObject(GameObject* object)
{
    for (auto it = m_objects.begin(); it != m_objects.end(); it++)
    {
        if ((*it).get() == object)
        {
            m_deleteList.push_back(it);
            return;
        }
    }
}

WeakPtr<GameObject> Scene::duplicateGameObject(const std::shared_ptr<GameObject>& object)
{
    auto object2 = std::make_shared<GameObject>(object->name);

    object2->m_transform = std::make_shared<Transform>(*object->m_transform);
    
    if (object->hasComponent<Sprite>())
    {
        object2->addComponent(new Sprite(*object->getComponent<Sprite>()));
    }

    m_objects.push_back(object2);

    return object2;
}

WeakPtr<GameObject> Scene::findGameObject(const std::string& name) const
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

    for (auto& it : m_deleteList)
    {
        if (*it)
        {
            (*it)->destroy();
            m_objects.erase(it);
        }
    }
    m_deleteList.clear();
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