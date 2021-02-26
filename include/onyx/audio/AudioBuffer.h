#pragma once

#include <string>

namespace Onyx
{

class AudioBuffer
{
    friend class AudioSource;

public:
    AudioBuffer(const std::string& path);
    ~AudioBuffer();

private:
    uint32_t m_id = 0;
};

}