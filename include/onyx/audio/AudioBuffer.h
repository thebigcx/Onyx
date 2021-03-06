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

    const std::string& getPath() const { return m_path; }

private:
    uint32_t m_id = 0;

    std::string m_path = "";
};

}