#include <onyx/scene/ScriptableObject.h>
#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>

namespace Onyx
{

WeakPtr<GameObject> ScriptableObject::createGameObject(const std::string& name)
{
    return Game::getInstance()->getScene()->createGameObject(name);
}

void ScriptableObject::destroy(const WeakPtr<GameObject>& go)
{
    Game::getInstance()->getScene()->removeGameObject(go.get());
}

void ScriptableObject::destroyThis()
{
    Game::getInstance()->getScene()->removeGameObject(object);
}

WeakPtr<GameObject> ScriptableObject::findGameObject(const std::string& name)
{
    return Game::getInstance()->getScene()->findGameObject(name);
}

}