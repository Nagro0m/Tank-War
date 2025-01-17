#pragma once
#include "CoreMinimal.h"

class SoundSample
{
	using SoundStatus = SoundSource::Status;

	float volume;
	Sound* sound;
	SoundBuffer buffer;
	string path;

public:
	FORCEINLINE void SetMuteStatus(const bool _isMuted)
	{
		UpdateVolume(_isMuted ? 0.0f : volume);
	}
	FORCEINLINE void SetVolume(const float _volume)
	{
		UpdateVolume(volume = _volume);
	}
	FORCEINLINE void SetLoop(const bool _isLoop)
	{
		sound->setLooping(_isLoop);
	}
	FORCEINLINE void SetPitch(const float _pitch)
	{
		sound->setPitch(_pitch);
	}

	FORCEINLINE bool IsVailable()const
	{
		return sound->getStatus() != SoundStatus::Playing;
	}
	FORCEINLINE float GetVolume()const
	{
		return sound->getVolume();
	}
	FORCEINLINE string GetPath()const
	{
		return path;
	}



private:
	FORCEINLINE void UpdateVolume(const float _volume)
	{
		sound->setVolume(_volume);
	}
	FORCEINLINE SoundStatus GetStatus()const
	{
		return sound->getStatus();
	}
public:
	SoundSample(const string& _path);
	~SoundSample();

public:
	void Play(const Time& _time = Time());
	void Pause();
	void Stop();
};

