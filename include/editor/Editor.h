#pragma once

#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>

namespace Onyx
{

class Editor : public Game
{
public:
    Editor();

    void onStart() override;
    void onUpdate(float dt) override;
    void onRender() override;
    void onDestroy() override;

    void createFramebuffer();

    void setSelectedObject(const WeakPtr<GameObject>& selected);

private:
    uint32_t m_framebuffer = 0;
    uint32_t m_fboColor = 0;

    Vector2u m_viewportSize;

    WeakPtr<GameObject> m_selected;
};

}