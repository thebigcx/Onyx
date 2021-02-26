#include <onyx/audio/Audio.h>

#include <dr_libs/dr_mp3.h>
#include <dr_libs/dr_wav.h>
#include <dr_libs/dr_flac.h>

#include <iostream>

namespace Onyx
{

void Audio::init()
{
    m_device = alcOpenDevice(nullptr);
    m_context = alcCreateContext(m_device, nullptr);
    alcMakeContextCurrent(m_context);
}

void Audio::finalize()
{
    alcDestroyContext(m_context);
    alcCloseDevice(m_device);
}

}