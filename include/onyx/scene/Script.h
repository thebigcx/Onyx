#pragma once

#include <onyx/scene/Component.h>
#include <onyx/scene/ScriptableObject.h>

#include <utility>
#include <functional>

namespace Onyx
{

template<typename T>
class Script : public Component
{
public:
    Script()
    {
        instantiateScript = []()
        {
            return new T();
        };

        destroyScript = [](Script* component)
        {
            delete component->instance;
            component->instance = nullptr;
        };

        instance = instantiateScript();
    }

    T* instance = nullptr;

    std::function<T*()> instantiateScript;
    std::function<void(Script*)> destroyScript;

    void update(float dt) override
    {
        if (!m_initialized)
        {
            instance->m_owner = object;
            instance->start();

            m_initialized = true;
        }

        if (instance)
            instance->update(dt);
    }

    void destroy() override
    {
        destroyScript(this);
    }

private:
    bool m_initialized = false;
};

}