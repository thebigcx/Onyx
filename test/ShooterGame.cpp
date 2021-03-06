#include "ShooterGame.h"

#include <onyx/scene/GameObject.h>
#include <onyx/scene/Sprite.h>
#include <onyx/renderer/Texture.h>
#include <onyx/core/Input.h>
#include <onyx/scene/Script.h>
#include <onyx/maths/Quaternion.h>
#include <onyx/core/AssetManager.h>
#include <onyx/maths/Math.h>

#include <GLFW/glfw3.h>

#include <algorithm>
#include <iostream>

class Bullet : public Onyx::Script
{
public:
    void onStart() override
    {
        
    }

    void onUpdate(float dt) override
    {
        auto transform = getTransform();
        transform->translation += direction * dt * speed;
    }

    static constexpr float speed = 3.f;

    bool fromPlayer = true;

    Onyx::Vector2f direction;
};

class Player : public Onyx::Script
{
public:
    void onStart() override
    {
        
    }

    void onUpdate(float dt) override
    {
        auto& translation = getTransform()->translation;

        if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_A))
        {
            if (translation.x > 0)
                translation.x -= dt * speed;
        }
        if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_D))
        {
            if (translation.x < 900)
                translation.x += dt * speed;
        }
    }

    static constexpr float speed = 3;
};

class BulletManager : public Onyx::Script
{
public:
    static Onyx::WeakPtr<Onyx::GameObject> createBullet(const Onyx::Vector2f& position)
    {
        auto bullet = createGameObject("Bullet");

        auto sprite = new Onyx::Sprite();
        sprite->setTexture(texture);
        sprite->setTexCoords(Onyx::Vector2f(8, 0), Onyx::Vector2f(16, 8));
        bullet->addComponent(sprite);

        bullet->addComponent(new Bullet());

        bullet->getTransform()->scale = Onyx::Vector2f(100, 100);
        bullet->getTransform()->translation = position;

        bullets.push_back(bullet);

        return bullet;
    }

    void onStart() override
    {
        texture = Onyx::AssetManager::getInstance()->getTexture("assets/shooter.png");
    }

    void onUpdate(float dt) override
    {
        bulletCooldown--;

        if (Onyx::Keyboard::isKeyPressed(GLFW_KEY_K))
        {
            if (bulletCooldown <= 0.f)
            {
                auto bullet = createBullet(findGameObject("Player")->getTransform()->translation);
                bullet->getComponent<Bullet>()->direction = Onyx::Vector2f(0, 1);

                bulletCooldown = 30;
            }
        }
        
        for (unsigned int i = 0; i < bullets.size(); i++)
        {
            if (bullets[i])
                if (bullets[i]->getTransform()->translation.y > 1000 || bullets[i]->getTransform()->translation.y < 0)
                {
                    destroy(bullets[i]);
                    bullets.erase(bullets.begin() + i);
                }
        }
    }

    static inline std::shared_ptr<Onyx::Texture> texture;

    static inline std::vector<Onyx::WeakPtr<Onyx::GameObject>> bullets;

    int bulletCooldown = 0;
};

class Alien : public Onyx::Script
{
public:
    void onStart() override
    {
        currentDirection = Onyx::Vector2f(Onyx::Math::random(-1, 1), Onyx::Math::random(-1, 1));
    }

    void onUpdate(float dt) override
    {
        getTransform()->translation += currentDirection;
        if (getTransform()->translation.x < 0)
        {
            currentDirection.x = -currentDirection.x;
        }
        if (getTransform()->translation.x > 900)
        {
            currentDirection.x = -currentDirection.x;
        }
        if (getTransform()->translation.y < 0)
        {
            currentDirection.y = -currentDirection.y;
        }
        if (getTransform()->translation.y > 900)
        {
            currentDirection.y = -currentDirection.y;
        }

        shootCooldown--;

        if (shootCooldown <= 0)
        {
            auto bullet = BulletManager::createBullet(getTransform()->translation);
            bullet->getComponent<Bullet>()->fromPlayer = false;
            bullet->getComponent<Bullet>()->direction = Onyx::Vector2f(0, -1);

            shootCooldown = 60;
        }
    }

    Onyx::Vector2f currentDirection;
    int shootCooldown = 60;
};

class AlienManager : public Onyx::Script
{
public:
    Onyx::WeakPtr<Onyx::GameObject> createAlien()
    {
        auto alien = createGameObject("Alien");

        auto sprite = new Onyx::Sprite();
        sprite->setTexture(Onyx::AssetManager::getInstance()->getTexture("assets/shooter.png"));
        sprite->setTexCoords(Onyx::Vector2f(16, 0), Onyx::Vector2f(24, 8));
        alien->addComponent(sprite);

        alien->addComponent(new Alien());

        alien->getTransform()->scale = Onyx::Vector2f(100, 100);
        alien->getTransform()->translation = Onyx::Vector2f(Onyx::Math::random(0, 900), 800);

        aliens.push_back(alien);

        return alien;
    }

    void onStart() override
    {

    }

    void onUpdate(float dt) override
    {
        alienCooldown--;
        if (alienCooldown <= 0)
        {
            createAlien();
            alienCooldown = Onyx::Math::random(30, 60);
        }
    }

    static inline std::vector<Onyx::WeakPtr<Onyx::GameObject>> aliens;

    int alienCooldown = 0;
};

ShooterGame::ShooterGame()
{
    
}

void ShooterGame::onStart()
{
    auto scene = std::make_shared<Onyx::Scene>("Shooter Scene");
    m_scenes.push_back(scene);

    m_currentScene = scene;
    m_currentScene->start();

    //getWindow()->setFullscreen();
    getWindow()->setWindowed(1000, 1000);

    auto texture = Onyx::AssetManager::getInstance()->getTexture("assets/shooter.png");
    
    auto player = scene->createGameObject("Player");

    auto sprite = new Onyx::Sprite();
    sprite->setTexture(texture);
    sprite->setTexCoords(Onyx::Vector2f(0, 0), Onyx::Vector2f(8, 8));
    player->addComponent(sprite);
    player->addComponent(new Player());

    player->getTransform()->scale = Onyx::Vector2f(100, 100);

    auto bulletManager = scene->createGameObject("Bullet Manager");
    bulletManager->addComponent(new BulletManager());

    auto alienManager = scene->createGameObject("Alien Manager");
    alienManager->addComponent(new AlienManager());
}

void ShooterGame::onUpdate(float dt)
{
    m_currentScene->update(dt);
}

void ShooterGame::onRender()
{
    m_currentScene->render();
}

void ShooterGame::onDestroy()
{
    for (auto& scene : m_scenes)
    {
        scene->destroy();
    }
}