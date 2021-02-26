#include <onyx/audio/AudioSource.h>
#include <onyx/audio/Audio.h>
#include <onyx/scene/GameObject.h>
#include <onyx/scene/Transform.h>
#include <onyx/core/Game.h>
#include <onyx/scene/Camera.h>
#include <onyx/scene/Scene.h>
#include <onyx/audio/AudioBuffer.h>
#include <onyx/core/AssetManager.h>

#include <AL/al.h>

namespace Onyx
{

AudioSource::AudioSource()
{
    alGenSources(1, &m_id);
}

AudioSource::AudioSource(const std::string& path)
{
    alGenSources(1, &m_id);
    setFile(path);
}

AudioSource::~AudioSource()
{
    alDeleteSources(1, &m_id);
}

void AudioSource::update(float dt)
{
    auto transform = object->getTransform();
    alSourcefv(m_id, AL_POSITION, &transform->translation.x);

    auto camera = Game::getInstance()->getScene()->getCamera();
    alListenerfv(AL_POSITION, &camera->transform.translation.x);
}

void AudioSource::setFile(const std::string& path)
{
    m_buffer = AssetManager::getInstance()->getAudio(path);
    alSourcei(m_id, AL_BUFFER, m_buffer->m_id);
}

void AudioSource::setBuffer(const std::shared_ptr<AudioBuffer>& buffer)
{
    m_buffer = buffer;
    alSourcei(m_id, AL_BUFFER, m_buffer->m_id);
}

void AudioSource::play() const
{
    alSourcePlay(m_id);
}

void AudioSource::pause() const
{
    alSourcePause(m_id);
}

void AudioSource::stop() const
{
    alSourceStop(m_id);
}

void AudioSource::rewind() const
{
    alSourceRewind(m_id);
}

}