#pragma once

#include <AL/al.h>
#include <AL/alc.h>

#include <string>
#include <cstdint>

namespace Onyx
{

class Audio
{
public:
    static void init();
    static void finalize();

    static uint32_t createBuffer(const std::string& path);

private:
    static inline ALCcontext* m_context = nullptr;
    static inline ALCdevice* m_device = nullptr;
};

}