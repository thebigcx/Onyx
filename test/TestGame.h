#include <onyx/Game.h>
#include <onyx/Scene.h>

class TestScene : public Onyx::Scene
{
public:
    void init() override;
    void update(float dt) override;
};

class TestGame : public Onyx::Game
{
public:
    TestGame();

private:
    std::shared_ptr<TestScene> m_scene;
};