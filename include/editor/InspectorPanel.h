#pragma once

#include <onyx/scene/Scene.h>

#include <memory>

namespace Onyx
{

class InspectorPanel
{
public:
    static void drawInspectorPanel(const WeakPtr<GameObject>& selected);

    static void drawComponents(const WeakPtr<GameObject>& object);

    template<typename T, typename F>
    static void drawComponent(const std::string& name, const WeakPtr<GameObject>& object, const F& fn);

    template<typename T>
    static void addComponent(const WeakPtr<GameObject>& go, const std::string& name);
};

}