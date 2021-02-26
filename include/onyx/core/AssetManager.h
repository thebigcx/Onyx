#pragma once

#include <unordered_map>
#include <string>
#include <memory>

namespace Onyx
{

template<typename T>
class AssetCache
{
public:
    AssetCache() {}
    ~AssetCache() {}

    void add(const std::string& name, const std::shared_ptr<T>& asset)
    {
        m_assets.emplace(std::make_pair(name, asset));
    }

    std::shared_ptr<T> get(const std::string& name)
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

private:
    std::unordered_map<std::string, std::shared_ptr<T>> m_assets;
};

class Texture;
class Shader;

class AssetManager
{
public:
    static AssetManager* getInstance()
    {
        static AssetManager manager;
        return &manager;
    }

    std::shared_ptr<Texture> getTexture(const std::string& path);
    std::shared_ptr<Shader> getShader(const std::string& vs, const std::string& fs);

private:
    AssetCache<Texture> m_textures;
    AssetCache<Shader> m_shaders;
};

}