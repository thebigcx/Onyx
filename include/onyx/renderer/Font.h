#pragma once

#include <onyx/maths/Vector2.h>

#include <string>
#include <unordered_map>

namespace Onyx
{

class Font
{
public:
    struct Character
    {
        Vector2f advance;
        Vector2f pos;
        Vector2f size;

        float texOffset;
    };

public:
    Font(const std::string& path, uint32_t pixelSize);

    const Font::Character& getCharacter(char character) const;

private:
    uint32_t m_texture = 0;

    uint32_t m_pixelSize;

    Vector2u m_atlasSize;

    std::unordered_map<char, Character> m_characters;
};

}