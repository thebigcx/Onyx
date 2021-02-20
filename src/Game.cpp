#include <onyx/Game.h>

namespace Onyx
{

Game::Game()
{
    m_window = std::make_unique<Window>(600, 600, "Game");
}

void Game::run()
{
    init();

    

    finalize();
}

}