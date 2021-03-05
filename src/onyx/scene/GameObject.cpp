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
    for (unsigned int i = 0; i < m_components.size(); i++)
    {
        m_components[i]->update(dt);
    }
}

void GameObject::render()
{
    for (unsigned int i = 0; i < m_components.size(); i++)
    {
        m_components[i]->render();
    }
}

void GameObject::destroy()
{
    for (unsigned int i = 0; i < m_components.size(); i++)
    {
        m_components[i]->destroy();
    }
}

}