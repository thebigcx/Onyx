#include <onyx/Scene.h>
#include <onyx/GameObject.h>
#include <onyx/renderer/Renderer.h>

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
    Renderer::render(Vector2f(0, 0), Vector2f(100, 100), Vector4f(1, 1, 1, 1));

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