#pragma once

#include <memory>

#include <onyx/Window.h>

namespace Onyx
{

class Game
{
public:
    Game();

    void run();

    virtual void init() {}
    virtual void update(float dt) {}
    virtual void finalize() {}

private:
    std::unique_ptr<Window> m_window;
};

}