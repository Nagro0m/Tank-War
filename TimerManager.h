#pragma once
#include "Singleton.h"

class Timer
{
	function<void()> callback;
	double currentTime;
	double duration;
	bool isRunning;
	bool isLoop;

public:
	FORCEINLINE bool IsRunning() const
	{
		return isRunning;
	}
	FORCEINLINE bool IsLoop() const
	{
		return isLoop;
	}
	FORCEINLINE double GetCurrentTime() const
	{
		return currentTime;
	}

public:
	Timer(const function<void()>& _callback, const Time& _time,
		const bool _startRunning = false, const bool _isLoop = false);

public:
	void Start();
	void Update(const float _deltaTime);
	void Stop();
	void Resume();
	void Reset();
	void Pause();
};

class TimerManager : public Singleton<TimerManager>
{
	set<Timer*> allTimers;

public:
	TimerManager();
	~TimerManager();

	void Update();
	void Pause();
};

