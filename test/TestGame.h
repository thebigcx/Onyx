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
    std::shared_ptr<Onyx::GameObject> m_sprite;
};

class TestGame : public Onyx::Game
{
public:
    TestGame();
};