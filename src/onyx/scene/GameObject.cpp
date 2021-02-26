#include <onyx/scene/GameObject.h>
#include <onyx/scene/Component.h>
#include <onyx/scene/Transform.h>

namespace Onyx
{

GameObject::GameObject(const std::string& name_)
    : name(name_)
{
    m_transform = std::make_shared<Transform>();
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

void GameObject::destroy()
{
    for (auto& component : m_components)
    {
        component->destroy();
    }
}

void GameObject::addComponent(Component* component)
{
    component->object = this;
    m_components.emplace_back(component);
}

}