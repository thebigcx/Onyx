#pragma once

#include <vector>
#include <memory>
#include <string>

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
    std::shared_ptr<T> getComponent()
    {
        for (auto& component : m_components)
        {
            if (dynamic_cast<T*>(component.get()) != nullptr)
            {
                return std::static_pointer_cast<T>(component);
            }
        }
        
        return nullptr;
    }

    const std::shared_ptr<Transform>& getTransform() const { return m_transform; }
    
    void addComponent(Component* component);

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