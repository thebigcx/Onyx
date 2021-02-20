#include <onyx/Window.h>

#include <GLFW/glfw3.h>

namespace Onyx
{

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
    glfwInit();

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
}

}