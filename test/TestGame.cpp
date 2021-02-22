#include "TestGame.h"

#include <onyx/scene/GameObject.h>
#include <onyx/scene/Sprite.h>
#include <onyx/renderer/Texture.h>
#include <onyx/core/Input.h>

#include <GLFW/glfw3.h>

TestScene::TestScene()
    : Scene("Test Scene")
{

}

void TestScene::init()
{
    //Onyx::Game::getInstance()->getWindow()->setFullscreen();
    Onyx::Game::getInstance()->getWindow()->setWindowed(1920, 1080);

    m_texture = std::make_shared<Onyx::Texture>("assets/test.png");

    m_sprite = std::make_shared<Onyx::GameObject>("Sprite");

    auto sprite = new Onyx::Sprite();
    sprite->setTexture(m_texture);
    m_sprite->addComponent(sprite);

    m_sprite->addComponent(new Onyx::AudioSource("assets/test.mp3"));

    m_sprite->getTransform()->scale = Onyx::Vector2f(100, 100);
    m_objects.push_back(m_sprite);

    m_sprite->getComponent<Onyx::AudioSource>()->play();
}

void TestScene::update(float dt)
{
    if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_UP))
    {
        m_sprite->getTransform()->translation.y += 10;
    }
    if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_DOWN))
    {
        m_sprite->getTransform()->translation.y -= 10;
    }
    if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_LEFT))
    {
        m_sprite->getTransform()->translation.x -= 10;
    }
    if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_RIGHT))
    {
        m_sprite->getTransform()->translation.x += 10;
    }
}

TestGame::TestGame()
{
    m_scenes.push_back(std::make_shared<TestScene>());
    changeScene("Test Scene");
}