#include "SoundSample.h"
#include "SoundManager.h"

SoundSample::SoundSample(const string& _path)
{
	const string& _finalPath = "Assets/Sounds/" + _path;
	if (!buffer.loadFromFile(_finalPath))
	{
		LOG(Error, "Cannot open sound with path : \'" + _finalPath + "\'");
		return;
	}
	path = _path;
	sound = new Sound(buffer);
	volume = GetVolume();
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
	sound->setPlayingOffset(_time);
	sound->play();
}

void SoundSample::Pause()
{
	sound->pause();
}

void SoundSample::Stop()
{
	sound->stop();
}
