#pragma once

#include <onyx/maths/Vector2.h>
#include <onyx/maths/Vector4.h>
#include <onyx/renderer/Shader.h>

#include <cstdint>
#include <memory>

namespace Onyx
{

struct Vertex
{
    Vector2f pos;
    Vector2f uv;
};

struct RendererData
{
    static const uint32_t MAX_SPRITES = 1024;
    static const uint32_t MAX_VERTICES = MAX_SPRITES * 4;
    static const uint32_t MAX_INDICES = MAX_VERTICES * 6/4;

    uint32_t vao = 0;
    uint32_t vbo = 0;
    uint32_t ebo = 0;

    Vertex* vertexBase;
    Vertex* vertexPtr;

    uint32_t vertexCount = 0;

    std::shared_ptr<Shader> shader;
};

class Renderer
{
public:
    static void init();
    static void finalize();

    static void start();
    static void render(const Vector2f& pos, const Vector2f& size, const Vector4f& color);
    static void end();

private:
    static inline RendererData m_data;
};

}