#include <onyx/scene/ScriptableObject.h>
#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>

namespace Onyx
{

void ScriptableObject::instantiate(const std::shared_ptr<GameObject>& go)
{
    Game::getInstance()->getScene()->addGameObject(go);
}

std::shared_ptr<GameObject> ScriptableObject::findGameObject(const std::string& name)
{
    return Game::getInstance()->getScene()->findGameObject(name);
}

}