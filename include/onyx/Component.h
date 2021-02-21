#pragma once

namespace Onyx
{

class GameObject;

class Component
{
public:
    virtual void update(float dt) = 0;
    virtual void render() = 0;
    virtual void init() = 0;

    GameObject* object = nullptr;
};

}