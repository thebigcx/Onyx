#pragma once

#include <onyx/maths/Vector2.h>

#include <string>
#include <cstdint>
#include <memory>

namespace Onyx
{

class Texture
{
public:
    Texture(const std::string& path);
    Texture(uint32_t width, uint32_t height, void* data);
    ~Texture();

    void bind(uint32_t slot = 0) const;
    void unbind(uint32_t slot = 0) const;

    Vector2u getSize() const { return Vector2u(m_width, m_height); }
    const std::string& getPath() const { return m_path; }

    uint32_t getId() const { return m_id; }

private:
    uint32_t m_id;
    uint32_t m_width, m_height;
    std::string m_path;
};

}