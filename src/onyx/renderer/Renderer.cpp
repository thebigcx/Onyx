#include <onyx/renderer/Renderer.h>
#include <onyx/core/Game.h>
#include <onyx/scene/Scene.h>
#include <onyx/renderer/Texture.h>

#include <GL/glew.h>

namespace Onyx
{

void Renderer::init()
{
    glCreateVertexArrays(1, &m_data.vao);
    glBindVertexArray(m_data.vao);

    glCreateBuffers(1, &m_data.vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_data.vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * RendererData::MAX_VERTICES, nullptr, GL_DYNAMIC_DRAW);

    glCreateBuffers(1, &m_data.ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.ebo);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, pos)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, uv)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, color)));
    glEnableVertexAttribArray(2);

    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, index)));
    glEnableVertexAttribArray(3);

    m_data.vertexBase = new Vertex[RendererData::MAX_VERTICES];
    m_data.vertexPtr = m_data.vertexBase;

    uint32_t* indices = new uint32_t[RendererData::MAX_INDICES];

    uint32_t offset = 0;
    for (uint32_t i = 0; i < RendererData::MAX_INDICES; i += 6, offset += 4)
    {
        indices[i + 0] = 0 + offset;
        indices[i + 1] = 1 + offset;
        indices[i + 2] = 2 + offset;

        indices[i + 3] = 2 + offset;
        indices[i + 4] = 3 + offset;
        indices[i + 5] = 0 + offset;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_data.ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * RendererData::MAX_INDICES, indices, GL_STATIC_DRAW);

    delete indices;

    m_data.shader = std::make_shared<Shader>("assets/Texture.vert", "assets/Texture.frag");

    uint32_t white = 0xffffffff;
    m_data.textures[0] = std::make_shared<Texture>(1, 1, &white);

    int32_t samplers[32];
    for (uint32_t i = 0; i < 32; i++)
        samplers[i] = i;

    m_data.shader->bind();
    m_data.shader->setIntArray("uTextures", samplers, 32);
}

void Renderer::finalize()
{
    delete m_data.vertexBase;

    glDeleteVertexArrays(1, &m_data.vao);
    glDeleteBuffers(1, &m_data.vbo);
    glDeleteBuffers(1, &m_data.ebo);
}

void Renderer::start()
{
    m_data.vertexPtr = m_data.vertexBase;
    m_data.vertexCount = 0;
    m_data.textureSlotIndex = 1;
}

void Renderer::render(const Vector2f& pos, const Vector2f& size, const Vector3f& color)
{
    //render(m_data.whiteTexture, pos, size, color);
}

void Renderer::render(const std::shared_ptr<Texture>& texture, const Vector2f& pos, const Vector2f& size, const Vector3f& color)
{
    render(texture, pos, size, Vector2f(0, 0), Vector2f(texture->getSize().x, texture->getSize().y), color);
}

void Renderer::render(const std::shared_ptr<Texture>& texture, const Vector2f& pos, const Vector2f& size, const Vector2f& uv1, const Vector2f& uv2, const Vector3f& color)
{
    float texIndex = 0.f;

    for (uint32_t i = 0; i < m_data.textureSlotIndex; i++)
    {
        if (m_data.textures[i] == texture)
        {
            texIndex = static_cast<float>(i);
            break;
        }
    }

    if (texIndex == 0.f)
    {
        if (m_data.textureSlotIndex >= 32)
        {
            end();
            start();
        }

        texIndex = static_cast<float>(m_data.textureSlotIndex);
        m_data.textures[m_data.textureSlotIndex] = texture;
        m_data.textureSlotIndex++;
    }

    Vector2f co1 = uv1 / texture->getSize();
    Vector2f co2 = uv2 / texture->getSize();

    const Vector2f uvs[4]
    {
        { co1.x, co1.y },
        { co2.x, co1.y },
        { co2.x, co2.y },
        { co1.x, co2.y }
    };

    m_data.vertexPtr->pos = pos;
    m_data.vertexPtr->uv = uvs[0];
    m_data.vertexPtr->color = color;
    m_data.vertexPtr->index = texIndex;
    m_data.vertexPtr++;

    m_data.vertexPtr->pos = { pos.x + size.x, pos.y };
    m_data.vertexPtr->uv = uvs[1];
    m_data.vertexPtr->color = color;
    m_data.vertexPtr->index = texIndex;
    m_data.vertexPtr++;

    m_data.vertexPtr->pos = { pos.x + size.x, pos.y + size.y };
    m_data.vertexPtr->uv = uvs[2];
    m_data.vertexPtr->color = color;
    m_data.vertexPtr->index = texIndex;
    m_data.vertexPtr++;

    m_data.vertexPtr->pos = { pos.x, pos.y + size.y };
    m_data.vertexPtr->uv = uvs[3];
    m_data.vertexPtr->color = color;
    m_data.vertexPtr->index = texIndex;
    m_data.vertexPtr++;

    m_data.vertexCount += 4;
}

void Renderer::render(const std::string& string, const std::shared_ptr<Font>& font)
{

}

void Renderer::end()
{
    glBindVertexArray(m_data.vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, m_data.vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertex) * m_data.vertexCount, m_data.vertexBase);

    m_data.shader->bind();
    m_data.shader->setMatrix4f("uTransform", Matrix4f(1.f));
    m_data.shader->setMatrix4f("uView", Game::getInstance()->getScene()->getCamera()->getViewMatrix());
    m_data.shader->setMatrix4f("uProjection", Game::getInstance()->getScene()->getCamera()->getProjectionMatrix());

    for (uint32_t i = 0; i < m_data.textureSlotIndex; i++)
    {
        m_data.textures[i]->bind(i);
    }

    glDrawElements(GL_TRIANGLES, m_data.vertexCount * 6/4, GL_UNSIGNED_INT, 0);
}

}