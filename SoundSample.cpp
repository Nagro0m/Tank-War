#include "SoundSample.h"
#include "SoundManager.h"
#include "Logger.h"

SoundSample::SoundSample(const string& _path)
{
	volume = 100.0f;
	path = _path;
	if (!buffer.loadFromFile(_path))
	{
		LOG(Error, "Invalid Path : " + _path);
		sound = nullptr;
		return;
	}
	sound = new Sound(buffer);
	SoundManager::GetInstance().RegisterSample(this);
}

SoundSample::~SoundSample()
{
	delete sound;
}

void SoundSample::Play(const Time& _time)
{
	if (GetStatus() == SoundStatus::Paused)
	{
		Stop();
	}
	SetVolume(volume);
	sound->play();
	sound->setPlayingOffset(_time);
}

void SoundSample::Pause()
{
	sound->pause();
}

void SoundSample::Stop()
{
	sound->stop();
}
