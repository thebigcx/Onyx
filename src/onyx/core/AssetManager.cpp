#include <onyx/core/AssetManager.h>
#include <onyx/renderer/Texture.h>
#include <onyx/renderer/Shader.h>

namespace Onyx
{

std::shared_ptr<Texture> AssetManager::getTexture(const std::string& path)
{
    if (m_textures.exists(path))
    {
        return m_textures.get(path);
    }

    auto texture = std::make_shared<Texture>(path);
    m_textures.add(path, texture);
    return texture;
}

std::shared_ptr<Shader> AssetManager::getShader(const std::string& vs, const std::string& fs)
{
    if (m_shaders.exists(vs))
    {
        return m_shaders.get(vs);
    }

    auto shader = std::make_shared<Shader>(vs, fs);
    m_shaders.add(vs, shader);
    return shader;
}

}