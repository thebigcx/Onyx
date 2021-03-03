#pragma once

#include <onyx/scene/GameObject.h>

#include <memory>

namespace Onyx
{

class Transform;

class Component
{
public:
    virtual ~Component() {}
    
    virtual void update(float dt) {}
    virtual void render() {}
    virtual void destroy() {}

    virtual void onCollision(GameObject* object) {}

    template<typename T>
    WeakPtr<T> getComponent() const
    {
        return object->getComponent<T>();
    }

    WeakPtr<Transform> getTransform() const
    {
        return object->getTransform();
    }

    GameObject* object = nullptr;
};

}