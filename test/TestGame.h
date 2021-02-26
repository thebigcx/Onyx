#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>
#include <onyx/audio/AudioSource.h>

class TestScene : public Onyx::Scene
{
public:
    TestScene();

    void init() override;
    void update(float dt) override;

private:
    std::shared_ptr<Onyx::Texture> m_texture;
    std::shared_ptr<Onyx::Texture> m_texture2;

    std::shared_ptr<Onyx::GameObject> m_sprite;

    std::vector<std::shared_ptr<Onyx::GameObject>> m_bullets;

    std::shared_ptr<Onyx::GameObject> m_bulletManager;
};

class TestGame : public Onyx::Game
{
public:
    TestGame();
};