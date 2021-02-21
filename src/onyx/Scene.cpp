#include <onyx/Scene.h>
#include <onyx/GameObject.h>
#include <onyx/renderer/Renderer.h>
#include <onyx/renderer/Texture.h>

namespace Onyx
{

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