#pragma once

#include <onyx/scene/Component.h>

#include <cstdint>
#include <string>

namespace Onyx
{

class AudioSource : public Component
{
public:
    AudioSource(const std::string& path);
    ~AudioSource();

    void update(float dt) override;

    void setFile(const std::string& path);
    
    void play() const;
    void pause() const;
    void stop() const;
    void rewind() const;

private:
    uint32_t m_id;
    uint32_t m_buffer;
};

}