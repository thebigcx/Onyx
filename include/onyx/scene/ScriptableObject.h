#pragma once

#include <onyx/scene/GameObject.h>

namespace Onyx
{

class ScriptableObject
{
    template<typename T>
    friend class Script;

public:
    virtual ~ScriptableObject() {}

protected:
    virtual void start() = 0;
    virtual void update(float dt) = 0;

    template<typename T>
    std::shared_ptr<T> getComponent() const
    {
        return m_owner->getComponent<T>();
    }

    const std::shared_ptr<Transform>& getTransform() const
    {
        return m_owner->getTransform();
    }

    static void instantiate(const std::shared_ptr<GameObject>& go);

    static std::shared_ptr<GameObject> findGameObject(const std::string& name);

private:
    GameObject* m_owner;
};

}