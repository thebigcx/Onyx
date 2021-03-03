#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>
#include <onyx/audio/AudioSource.h>

class ShooterScene : public Onyx::Scene
{
public:
    ShooterScene();

    void init() override;
    void update(float dt) override;

private:
};

class ShooterGame : public Onyx::Game
{
public:
    ShooterGame();
};