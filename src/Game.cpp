#include <onyx/Game.h>
#include <onyx/Scene.h>
#include <onyx/renderer/Renderer.h>

#include <GL/glew.h>

namespace Onyx
{

Game::Game()
{
    m_instance = this;
    m_window = std::make_unique<Window>(600, 600, "Game");

    Renderer::init();
}

void Game::run()
{
    while (m_window->isOpen())
    {
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_scene->internalUpdate(5);
        m_scene->internalRender();

        m_window->update();
    }

    Renderer::finalize();
}

void Game::changeScene(const std::shared_ptr<Scene>& scene)
{
    m_scene = scene;
    m_scene->internalInit();
}

}