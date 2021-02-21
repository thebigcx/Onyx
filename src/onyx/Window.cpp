#include <onyx/Window.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace Onyx
{

static void windowResizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Window::Window(uint32_t width, uint32_t height, const std::string& title)
{
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwSetFramebufferSizeCallback(m_window, windowResizeCallback);

    glfwMakeContextCurrent(m_window);
    glewInit();

    glViewport(0, 0, width, height);
}

void Window::update() const
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

bool Window::isOpen() const
{
    return !glfwWindowShouldClose(m_window);
}

void Window::setSize(const Vector2u& size)
{
    glfwSetWindowSize(m_window, size.x, size.y);
}

Vector2u Window::getSize() const
{
    int width, height;
    glfwGetWindowSize(m_window, &width, &height);
    return Vector2u(width, height);
}

}