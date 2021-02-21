#include "TestGame.h"

#include <onyx/GameObject.h>
#include <onyx/Game.h>

void TestScene::init()
{
    Onyx::Game::getInstance()->getWindow()->setSize(Onyx::Vector2u(1920, 1080));
}

void TestScene::update(float dt)
{
    
}

TestGame::TestGame()
{
    m_scene = std::make_shared<TestScene>();
    changeScene(m_scene);
}