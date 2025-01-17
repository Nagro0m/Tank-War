#include "SoundManager.h"

SoundManager::SoundManager()
{
	allSamples = multimap<string, SoundSample*>();
	isMuted = false;
	Volume = 1.0f;
}

SoundManager::~SoundManager()
{
	for (pair<string, SoundSample*> _samplePair : allSamples)
	{
		delete _samplePair.second;
	}
}

SoundSample* SoundManager::PlaySound(const string& _path, const ExtensionType& _type)
{

	const string& _finalPath = prefixPath + _path + GetExtension(_type);

	using Iterator = multimap<string, SoundSample*>::iterator;

	const pair<Iterator, Iterator>& _activeSample = allSamples.equal_range(_path);
	SoundSample* _sample;
	for (Iterator _iterator = _activeSample.first; _iterator != _activeSample.second; ++_iterator)
	{
		_sample = _iterator->second;
		if (_sample->IsVailable())
		{
			_sample->SetMuteStatus(isMuted);
			_sample->Play();
			return _sample;
		}
	}

	_sample = new SoundSample(_finalPath);
	_sample->Play();
	return _sample;
}

void SoundManager::ToogleMute()
{
	isMuted = !isMuted;
	for (pair<string, SoundSample*> _samplePair : allSamples)
	{
		_samplePair.second->SetMuteStatus(isMuted);
	}
}
