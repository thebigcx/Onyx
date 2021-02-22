#include <onyx/core/Input.h>
#include <onyx/core/Game.h>

#include <GLFW/glfw3.h>

namespace Onyx
{

bool Keyboard::isKeyPressed(int key)
{
    auto window = Game::getInstance()->getWindow();
    return glfwGetKey(window->getNative(), key) == GLFW_PRESS;
}

bool Mouse::isMousePressed(int button)
{
    auto window = Game::getInstance()->getWindow();
    return glfwGetMouseButton(window->getNative(), button);
}

Vector2u Mouse::getMousePosition()
{
    auto window = Game::getInstance()->getWindow();

    double x, y;
    glfwGetCursorPos(window->getNative(), &x, &y);
    
    return Vector2u(x, y);
}

}