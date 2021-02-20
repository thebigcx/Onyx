#include <onyx/Game.h>

class TestGame : public Onyx::Game
{
public:
    TestGame();

    void init() override;
    void update(float dt) override;
    void finalize() override;
};