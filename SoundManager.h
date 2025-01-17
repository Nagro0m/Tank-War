#pragma once
#include "Singleton.h"
#include "SoundSample.h"
enum ExtensionType
{
	MP3,
	WAV
};

class SoundManager : public Singleton<SoundManager>
{
	multimap<string, SoundSample*> allSamples;
	bool isMuted;
	float Volume;
	string prefixPath;

public:
	FORCEINLINE void RegisterSample(SoundSample* _sample)
	{
		allSamples.insert({ _sample->GetPath(), _sample });
	}

	FORCEINLINE string GetExtension(const ExtensionType& _type)
	{
		return vector<string>({".mp3", ".wav"})[_type];
	}

public:
	SoundManager();
	~SoundManager();

public:
	SoundSample* PlaySound(const string& _path, const ExtensionType& _type);
	void ToogleMute();
};

