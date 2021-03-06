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
}

void Game::run()
{
    m_window = std::make_unique<Window>(600, 600, "Game");

    Renderer::init();
    Audio::init();

    onStart();

    while (m_window->isOpen())
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        onUpdate(5);
        onRender();

        m_window->update();
    }

    onDestroy();

    Renderer::finalize();
    Audio::finalize();
}

void Game::changeScene(const std::string& name)
{
    for (auto& scene : m_scenes)
    {
        if (scene->name == name)
        {
            m_currentScene = scene;
            m_currentScene->start();
            return;
        }
    }
}

}