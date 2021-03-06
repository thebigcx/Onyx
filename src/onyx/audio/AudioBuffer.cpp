#include <onyx/audio/AudioBuffer.h>

#include <AL/al.h>

#include <dr_libs/dr_flac.h>
#include <dr_libs/dr_wav.h>
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
    drwav wav;
    if (!drwav_init_file(&wav, path.c_str(), nullptr))
    {
        std::cout << "Could not open MP3 file: " << path << "\n";
        return 0;
    }

    size_t dataSize = wav.totalPCMFrameCount * wav.channels * sizeof(drwav_int16);
    drwav_int16* data = (drwav_int16*)malloc(dataSize);
    drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, data);

    uint32_t buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_STEREO16, data, dataSize, wav.sampleRate);

    drwav_uninit(&wav);
    free(data);

    return buffer;
}

static uint32_t loadFlac(const std::string& path)
{
    drflac* flac;
    if (!(flac = drflac_open_file(path.c_str(), nullptr)))
    {
        std::cout << "Could not open MP3 file: " << path << "\n";
        return 0;
    }

    size_t dataSize = flac->totalPCMFrameCount * flac->channels * sizeof(drflac_int16);
    drflac_int16* data = (drflac_int16*)malloc(dataSize);
    drflac_read_pcm_frames_s16(flac, flac->totalPCMFrameCount, data);

    uint32_t buffer;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_STEREO16, data, dataSize, flac->sampleRate);

    drflac_close(flac);
    free(data);

    return buffer;
}

AudioBuffer::AudioBuffer(const std::string& path)
    : m_path(path)
{
    auto extension = path.substr(path.find_last_of(".") + 1);

    if (extension == "wav")
    {
        m_id = loadWav(path);
    }
    else if (extension == "mp3")
    {
        m_id = loadMp3(path);
    }
    else if (extension == "flac")
    {
        m_id = loadFlac(path);
    }
    else
    {
        std::cout << "Unsupported audio file format: " << extension << "\n";
    }
}

AudioBuffer::~AudioBuffer()
{
    alDeleteBuffers(1, &m_id);
}

}