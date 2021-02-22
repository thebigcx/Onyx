#include <onyx/scene/Scene.h>
#include <onyx/scene/GameObject.h>
#include <onyx/renderer/Renderer.h>
#include <onyx/renderer/Texture.h>

namespace Onyx
{

Scene::Scene(const std::string& name_)
    : name(name_)
{
    
}

void Scene::internalUpdate(float dt)
{
    for (auto& object : m_objects)
    {
        object->update(dt);
    }

    update(dt);
}

void Scene::internalRender()
{
    Renderer::start();

    for (auto& object : m_objects)
    {
        object->render();
    }

    Renderer::end();
}

void Scene::internalInit()
{
    m_camera = std::make_shared<Camera>();

    for (auto& object : m_objects)
    {
        object->init();
    }

    init();
}

}