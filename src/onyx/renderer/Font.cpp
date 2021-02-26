#include <onyx/renderer/Font.h>

#include <GL/glew.h>

#include <ft2build.h>
#include FT_FREETYPE_H

namespace Onyx
{

Font::Font(const std::string& path, uint32_t pixelSize)
    : m_pixelSize(pixelSize)
{
    FT_Library library;
    FT_Init_FreeType(&library);

    FT_Face face;
    FT_New_Face(library, path.c_str(), 0, &face);

    FT_Set_Pixel_Sizes(face, 0, pixelSize);

    FT_GlyphSlot g = face->glyph;
    unsigned int w = 0;
    unsigned int h = 0;

    for (unsigned int i = 32; i < 255; i++)
    {
        FT_Load_Char(face, i, FT_LOAD_RENDER);

        w += g->bitmap.width;
        h = std::max(h, static_cast<unsigned int>(g->bitmap.rows));
    }

    m_atlasSize = Vector2u(w, h);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glCreateTextures(GL_TEXTURE_2D, 1, &m_texture);
    glBindTextureUnit(0, m_texture);
    glTextureStorage2D(m_texture, 1, GL_RGBA8, m_atlasSize.x, m_atlasSize.y);

    unsigned int x = 0;
    for (unsigned int i = 32; i < 255; i++)
    {
        FT_Load_Char(face, i, FT_LOAD_RENDER);

        glTextureSubImage2D(m_texture, 0, x, 0, g->bitmap.width, g->bitmap.rows, GL_RED, GL_UNSIGNED_BYTE, g->bitmap.buffer);

        m_characters[i].advance = Vector2f(g->advance.x >> 6, g->advance.y >> 6);
        m_characters[i].size = Vector2f(g->bitmap.width, g->bitmap.rows);
        m_characters[i].pos = Vector2f(g->bitmap_left, g->bitmap_top);
        m_characters[i].texOffset = static_cast<float>(x) / m_atlasSize.x;

        x += g->bitmap.width;
    }

    FT_Done_Face(face);
    FT_Done_FreeType(library);
}

const Font::Character& Font::getCharacter(char character) const
{
    return m_characters.at(character);
}

}