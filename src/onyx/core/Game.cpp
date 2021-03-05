#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>
#include <onyx/renderer/Renderer.h>
#include <onyx/audio/Audio.h>

#include <GL/glew.h>

namespace Onyx
{

Game::Game()
{
    m_instance = this;
    m_window = std::make_unique<Window>(600, 600, "Game");

    Renderer::init();
    Audio::init();
}

void Game::run()
{
    while (m_window->isOpen())
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_scene->update(5);
        m_scene->render();

        m_window->update();
    }

    for (auto& scene : m_scenes)
    {
        scene->destroy();
        scene.reset();
    }
    m_scene = nullptr;

    Renderer::finalize();
    Audio::finalize();
}

void Game::changeScene(const std::string& name)
{
    for (auto& scene : m_scenes)
    {
        if (scene->name == name)
        {
            m_scene.reset();
            m_scene = scene;
            m_scene->start();
            return;
        }
    }
}

}