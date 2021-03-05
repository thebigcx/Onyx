#include <onyx/scene/Scene.h>
#include <onyx/scene/GameObject.h>
#include <onyx/renderer/Renderer.h>
#include <onyx/renderer/Font.h>
#include <onyx/scene/Component.h>
#include <onyx/scene/Sprite.h>

#include <iostream>
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

void Scene::removeGameObject(const WeakPtr<GameObject>& object)
{
    m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object.lock()), m_objects.end());
}

WeakPtr<GameObject> Scene::duplicateGameObject(const WeakPtr<GameObject>& object)
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
    for (unsigned int i = 0; i < m_objects.size(); i++)
    {
        if (m_objects[i]->name == name)
        {
            return m_objects[i];
        }
    }

    return nullptr;
}

void Scene::update(float dt)
{
    // All m_objects iterations must use indices, as Script components have the ability
    // to add and remove objects, invalidating iterators. Same goes for components.
    for (unsigned int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->update(dt);
    }
}

void Scene::render()
{
    Renderer::start();

    for (unsigned int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->render();
    }

    Renderer::end();
}

void Scene::start()
{
    m_camera = std::make_shared<Camera>();

    onStart();
}

void Scene::destroy()
{
    for (unsigned int i = 0; i < m_objects.size(); i++)
    {
        m_objects[i]->destroy();
    }
}

}