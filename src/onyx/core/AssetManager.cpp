#include <onyx/core/AssetManager.h>
#include <onyx/renderer/Texture.h>
#include <onyx/renderer/Shader.h>
#include <onyx/audio/AudioBuffer.h>

namespace Onyx
{

void AssetManager::flush()
{
    m_textures.flush();
    m_shaders.flush();
    m_audios.flush();
}

WeakPtr<Texture> AssetManager::getTexture(const std::string& path)
{
    if (m_textures.exists(path))
    {
        return m_textures.get(path);
    }

    auto texture = std::make_shared<Texture>(path);
    m_textures.add(path, texture);
    return texture;
}

WeakPtr<Shader> AssetManager::getShader(const std::string& vs, const std::string& fs)
{
    if (m_shaders.exists(vs))
    {
        return m_shaders.get(vs);
    }

    auto shader = std::make_shared<Shader>(vs, fs);
    m_shaders.add(vs, shader);
    return shader;
}

WeakPtr<AudioBuffer> AssetManager::getAudio(const std::string& path)
{
    if (m_audios.exists(path))
    {
        return m_audios.get(path);
    }

    auto audio = std::make_shared<AudioBuffer>(path);
    m_audios.add(path, audio);
    return audio;
}

}