#pragma once

#include <onyx/scene/Component.h>

#include <cstdint>
#include <string>
#include <memory>

namespace Onyx
{

class AudioBuffer;

class AudioSource : public Component
{
public:
    AudioSource();
    AudioSource(const std::string& path);
    ~AudioSource();

    void update(float dt) override;

    void setFile(const std::string& path);
    void setBuffer(const std::shared_ptr<AudioBuffer>& buffer);
    
    void play() const;
    void pause() const;
    void stop() const;
    void rewind() const;

private:
    uint32_t m_id;
    
    std::shared_ptr<AudioBuffer> m_buffer;
};

}