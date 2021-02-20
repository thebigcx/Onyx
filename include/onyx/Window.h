#pragma once

#include <cstdint>
#include <string>

struct GLFWwindow;

namespace Onyx
{

class Window
{
public:
    Window(uint32_t width, uint32_t height, const std::string& title);

private:
    GLFWwindow* m_window = nullptr;
};

}