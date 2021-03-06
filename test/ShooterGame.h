#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>
#include <onyx/audio/AudioSource.h>

class ShooterGame : public Onyx::Game
{
public:
    ShooterGame();

    void onStart() override;
    void onUpdate(float dt) override;
    void onRender() override;
    void onDestroy() override;
};