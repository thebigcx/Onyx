#pragma once

namespace Onyx
{

class ImGuiLayer
{
public:
    static void init();
    static void beginFrame();
    static void endFrame();
    static void destroy();
};

}