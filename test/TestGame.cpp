#include "TestGame.h"

#include <onyx/scene/GameObject.h>
#include <onyx/scene/Sprite.h>
#include <onyx/renderer/Texture.h>
#include <onyx/core/Input.h>
#include <onyx/scene/ScriptableObject.h>
#include <onyx/scene/Script.h>
#include <onyx/maths/Quaternion.h>
#include <onyx/core/AssetManager.h>

#include <GLFW/glfw3.h>

class Bullet : public Onyx::ScriptableObject
{
public:
    Bullet()
    {
        
    }

    void start() override
    {
        
    }

    void update(float dt) override
    {
        auto transform = getTransform();
        transform->translation += direction;
    }

    Onyx::Vector2f direction;
};

class Player : public Onyx::ScriptableObject
{
public:
    Player() {}

    void start() override
    {

    }

    void update(float dt) override
    {
        if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_UP))
        {
            getTransform()->translation.y += 10;
        }
        if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_DOWN))
        {
            getTransform()->translation.y -= 10;
        }
        if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_LEFT))
        {
            getTransform()->translation.x -= 10;
        }
        if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_RIGHT))
        {
            getTransform()->translation.x += 10;
        }
    }
};

class BulletManager : public Onyx::ScriptableObject
{
public:
    BulletManager() {}

    std::shared_ptr<Onyx::GameObject> createBullet(const Onyx::Vector2f& position, float direction)
    {
        auto object = std::make_shared<Onyx::GameObject>("Bullet");

        auto sprite = new Onyx::Sprite();
        sprite->setTexture(texture);
        sprite->setTexCoords(Onyx::Vector2f(0, 240), Onyx::Vector2f(16, 256));
        object->addComponent(sprite);

        auto script = new Onyx::Script<Bullet>();
        script->instance->direction = Onyx::Vector2f(0, 1);
        object->addComponent(script);

        object->getTransform()->scale = Onyx::Vector2f(100, 100);
        object->getTransform()->translation = position;

        return object;
    }

    void start() override
    {
        texture = Onyx::AssetManager::getInstance()->getTexture("assets/test.png");
    }

    void update(float dt) override
    {
        if (Onyx::Mouse::isMousePressed(GLFW_MOUSE_BUTTON_LEFT))
        {
            bullets.push_back(createBullet(findGameObject("Player")->getTransform()->translation, 100));
            instantiate(bullets.back());
        }
    }

    std::shared_ptr<Onyx::Texture> texture;

    std::vector<std::shared_ptr<Onyx::GameObject>> bullets;
};

TestScene::TestScene()
    : Scene("Test Scene")
{

}

void TestScene::init()
{
    Onyx::Game::getInstance()->getWindow()->setFullscreen();
    //Onyx::Game::getInstance()->getWindow()->setWindowed(1920, 1080);

    m_texture = Onyx::AssetManager::getInstance()->getTexture("assets/test.png");
    m_texture2 = Onyx::AssetManager::getInstance()->getTexture("assets/test2.png");
    
    m_sprite = std::make_shared<Onyx::GameObject>("Player");

    auto sprite = new Onyx::Sprite();
    sprite->setTexture(m_texture);
    sprite->setTexCoords(Onyx::Vector2f(0, 240), Onyx::Vector2f(16, 256));
    m_sprite->addComponent(sprite);
    m_sprite->addComponent(new Onyx::Script<Player>());

    m_sprite->getTransform()->scale = Onyx::Vector2f(100, 100);
    addGameObject(m_sprite);

    m_bulletManager = std::make_shared<Onyx::GameObject>("Bullet Manager");
    m_bulletManager->addComponent(new Onyx::Script<BulletManager>());
    addGameObject(m_bulletManager);
}

void TestScene::update(float dt)
{

}

TestGame::TestGame()
{
    m_scenes.push_back(std::make_shared<TestScene>());
    changeScene("Test Scene");
}