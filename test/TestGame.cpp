#include "TestGame.h"

#include <onyx/GameObject.h>
#include <onyx/Game.h>
#include <onyx/Sprite.h>
#include <onyx/renderer/Texture.h>

void TestScene::init()
{
    Onyx::Game::getInstance()->getWindow()->setSize(Onyx::Vector2u(1920, 1080));

    m_texture = std::make_shared<Onyx::Texture>("assets/test.png");

    auto object = std::make_shared<Onyx::GameObject>("Sprite");

    auto sprite = new Onyx::Sprite();
    sprite->setTexture(m_texture);
    object->addComponent(sprite);

    object->getTransform()->scale = Onyx::Vector2f(100, 100);
    m_objects.push_back(object);
}

void TestScene::update(float dt)
{
    
}

TestGame::TestGame()
{
    m_scene = std::make_shared<TestScene>();
    changeScene(m_scene);
}