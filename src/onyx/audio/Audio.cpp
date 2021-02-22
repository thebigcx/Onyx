#include <onyx/audio/Audio.h>

#include <dr_libs/dr_mp3.h>

#include <iostream>

namespace Onyx
{

static uint32_t loadMp3(const std::string& path)
{
    drmp3 mp3;
    if (!drmp3_init_file(&mp3, path.c_str(), nullptr))
    {
        std::cout << "Could not open MP3 file: " << path << "\n";
        return 0;
    }

    drmp3_uint64 frameCount;
    drmp3_get_mp3_and_pcm_frame_count(&mp3, nullptr, &frameCount);

    size_t dataSize = frameCount * mp3.channels * sizeof(drmp3_int16);
    drmp3_int16* data = (drmp3_int16*)malloc(dataSize);
    drmp3_read_pcm_frames_s16(&mp3, frameCount, data);

    uint32_t buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_STEREO16, data, dataSize, mp3.sampleRate);

    drmp3_uninit(&mp3);
    free(data);

    return buffer;
}

static uint32_t loadWav(const std::string& path)
{

}

static uint32_t loadFlac(const std::string& path)
{

}

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

uint32_t Audio::createBuffer(const std::string& path)
{
    auto extension = path.substr(path.find_last_of(".") + 1);
    if (extension == "wav")
    {
        return loadWav(path);
    }
    else if (extension == "mp3")
    {
        return loadMp3(path);
    }
    else if (extension == "flac")
    {
        return loadFlac(path);
    }
}

}