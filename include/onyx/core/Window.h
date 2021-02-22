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

    void setFullscreen() const;
    void setWindowed(uint32_t width, uint32_t height) const;

    void setSize(const Vector2u& size);

    Vector2u getSize() const;

    GLFWwindow* getNative() const { return m_window; }

private:
    GLFWwindow* m_window = nullptr;
};

}