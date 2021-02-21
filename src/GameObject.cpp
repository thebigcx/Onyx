#include <onyx/GameObject.h>
#include <onyx/Component.h>

namespace Onyx
{

GameObject::GameObject(const std::string& name)
    : m_name(name)
{

}

void GameObject::init()
{
    
}

void GameObject::update(float dt)
{
    for (auto& component : m_components)
    {
        component->update(dt);
    }
}

void GameObject::render()
{
    for (auto& component : m_components)
    {
        component->render();
    }
}

void GameObject::addComponent(Component* component)
{
    m_components.emplace_back(component);
}

}