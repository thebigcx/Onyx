#pragma once

namespace Onyx
{

class GameObject;

class Component
{
public:
    virtual ~Component() {}
    
    virtual void update(float dt) {}
    virtual void render() {}
    virtual void destroy() {}

    GameObject* object = nullptr;
};

}