#pragma once

#include <onyx/core/Core.h>

#include <unordered_map>
#include <string>
#include <memory>

namespace Onyx
{

template<typename T>
class AssetCache
{
public:
    ~AssetCache()
    {
        m_assets.clear();
    }

    void add(const std::string& name, const std::shared_ptr<T>& asset)
    {
        m_assets.emplace(std::make_pair(name, asset));
    }

    WeakPtr<T> get(const std::string& name)
    {
        return m_assets[name];
    }

    void remove(const std::string& name)
    {
        if (exists(name))
        {
            m_assets.erase(m_assets.find(name));
        }
    }

    bool exists(const std::string& name)
    {
        return m_assets.find(name) != m_assets.end();
    }

    void flush()
    {
        m_assets.clear();
    }

private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_assets;
};

class Texture;
class Shader;
class AudioBuffer;

class AssetManager
{
public:
    static AssetManager* getInstance()
    {
        static AssetManager manager;
        return &manager;
    }

    void flush();

    WeakPtr<Texture> getTexture(const std::string& path);
    WeakPtr<Shader> getShader(const std::string& vs, const std::string& fs);
    WeakPtr<AudioBuffer> getAudio(const std::string& path);

private:
    AssetCache<Texture> m_textures;
    AssetCache<Shader> m_shaders;
    AssetCache<AudioBuffer> m_audios;
};

}