#pragma once

#include <cstdint>
#include <string>

#include <onyx/maths/Vector2.h>

struct GLFWwindow;

namespace Onyx
{

class Window
{
public:
    Window(uint32_t width, uint32_t height, const std::string& title);

    void update() const;
    bool isOpen() const;

    void setSize(const Vector2u& size);

    Vector2u getSize() const;

private:
    GLFWwindow* m_window = nullptr;
};

}