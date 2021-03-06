#pragma once

#include <onyx/scene/Scene.h>

#include <memory>

namespace Onyx
{

class ScenePanel
{
public:
    static void drawScenePanel(const std::shared_ptr<Scene>& scene);
};

}