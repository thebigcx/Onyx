#pragma once

#include <vector>
#include <memory>
#include <string>

namespace Onyx
{

class Component;

class GameObject
{
public:
    GameObject(const std::string& name);

    void init();
    void update(float dt);
    void render();

    template<typename T>
    std::shared_ptr<T> getComponent()
    {
        for (auto& component : m_components)
        {
            if (dynamic_cast<T>(component) != nullptr)
            {
                return component;
            }
        }
    }

    void addComponent(Component* component);

private:
    std::string m_name;

    std::vector<std::shared_ptr<Component>> m_components;
};

}