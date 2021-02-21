#pragma once

#include <onyx/maths/Vector2.h>

#include <string>
#include <cstdint>

namespace Onyx
{

class Texture
{
public:
    Texture(const std::string& path);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind(uint32_t slot = 0) const;

    Vector2u getSize() const { return Vector2u(m_width, m_height); }
    const std::string& getPath() const { return m_path; }

private:
    uint32_t m_id;
    uint32_t m_width, m_height;
    std::string m_path;
};

}