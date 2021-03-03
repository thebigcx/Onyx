#pragma once

#include <onyx/core/Core.h>

#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <typeindex>

namespace Onyx
{

class Component;
class Transform;

class GameObject
{
    friend class Scene;

public:
    GameObject(const std::string& name_);

    template<typename T>
    WeakPtr<T> getComponent()
    {
        for (auto& component : m_components)
        {
            if (dynamic_cast<T*>(component.get()) != nullptr) // TODO: don't use dynamic cast
            {
                return std::static_pointer_cast<T>(component);
            }
        }
        
        return nullptr;
    }

    WeakPtr<Transform> getTransform() const { return m_transform; }
    
    template<typename T>
    void addComponent(T* component)
    {
        component->object = this;
        m_components.emplace_back(component);
    }

    template<typename T>
    bool hasComponent()
    {
        for (auto& component : m_components)
        {
            if (dynamic_cast<T*>(component.get()) != nullptr)
            {
                return true;
            }
        }

        return false;
    }

    void onCollision(GameObject* other);

    std::string name;

private:
    void update(float dt);
    void render();
    void destroy();

private:
    std::vector<std::shared_ptr<Component>> m_components;

    std::shared_ptr<Transform> m_transform;
};

}