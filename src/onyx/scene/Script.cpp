#include <onyx/scene/Script.h>
#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>

namespace Onyx
{

WeakPtr<GameObject> Script::createGameObject(const std::string& name)
{
    return Game::getInstance()->getScene()->createGameObject(name);
}

void Script::destroy(const WeakPtr<GameObject>& go)
{
    Game::getInstance()->getScene()->removeGameObject(go);
}

void Script::destroyThis()
{
    //Game::getInstance()->getScene()->removeGameObject(object);
}

WeakPtr<GameObject> Script::findGameObject(const std::string& name)
{
    return Game::getInstance()->getScene()->findGameObject(name);
}

}