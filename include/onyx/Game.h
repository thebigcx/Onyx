#pragma once

#include <memory>

#include <onyx/Window.h>

namespace Onyx
{

class Scene;

class Game
{
public:
    Game();

    void run();

    void changeScene(const std::shared_ptr<Scene>& scene);

    const std::shared_ptr<Scene>& getScene() const { return m_scene; }
    const std::shared_ptr<Window>& getWindow() const { return m_window; }

    static Game* getInstance()
    {
        return m_instance;
    }

private:
    static inline Game* m_instance = nullptr;

    std::shared_ptr<Window> m_window = nullptr;

    std::shared_ptr<Scene> m_scene = nullptr;
};

}