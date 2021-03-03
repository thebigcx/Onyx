#pragma once

#include <onyx/scene/GameObject.h>
#include <onyx/scene/Component.h>
#include <onyx/core/Core.h>

namespace Onyx
{

class ScriptableObject : public Component
{
    template<typename T>
    friend class Script;

public:
    virtual ~ScriptableObject() {}

protected:
    virtual void onStart() = 0;
    virtual void onUpdate(float dt) = 0;

    static WeakPtr<GameObject> createGameObject(const std::string& name);
    static void destroy(const WeakPtr<GameObject>& go);
    void destroyThis();

    static WeakPtr<GameObject> findGameObject(const std::string& name);

private:
    void update(float dt) override
    {
        if (!m_initialized)
        {
            onStart();
            m_initialized = true;
        }

        onUpdate(dt);
    }

private:
    bool m_initialized = false;
};

}