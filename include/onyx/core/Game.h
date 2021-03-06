#pragma once

#include <memory>
#include <vector>

#include <onyx/core/Window.h>

namespace Onyx
{

class Scene;

class Game
{
public:
    Game();

    virtual void onStart() {}
    virtual void onUpdate(float dt) {}
    virtual void onRender() {}
    virtual void onDestroy() {}

    void run();

    void changeScene(const std::string& name);

    const std::shared_ptr<Scene>& getScene() const { return m_currentScene; }
    const std::shared_ptr<Window>& getWindow() const { return m_window; }

    static Game* getInstance()
    {
        return m_instance;
    }

protected:
    std::shared_ptr<Scene> m_currentScene;
    std::vector<std::shared_ptr<Scene>> m_scenes;

private:
    static inline Game* m_instance = nullptr;

    std::shared_ptr<Window> m_window = nullptr;
};

}