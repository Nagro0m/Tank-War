#include "TimerManager.h"

Timer::Timer(const function<void()>& _callback, const Time& _time, const bool _startRunning, const bool _isLoop)
{
	isRunning = _startRunning;
	isLoop = _isLoop;
	currentTime = 0.0;
	duration = _time.asMilliseconds();
	callback = _callback;
}

void Timer::Start()
{
	Reset();
	Resume();
}

void Timer::Update(const float _deltaTime)
{
	if (!isRunning) return;

	currentTime += _deltaTime;
	if (currentTime >= duration)
	{
		if (callback)
		{
			callback();
		}
		if (!isLoop)
		{
			Stop();
		}
		Reset();
	}
}

void Timer::Stop()
{
//Remove
}

void Timer::Resume()
{
	isRunning = true;
}

void Timer::Reset()
{
	currentTime = 0.0;
}

void Timer::Pause()
{
	isRunning = false;
}

TimerManager::TimerManager()
{
	allTimers = set<Timer*>();

}

TimerManager::~TimerManager()
{
	for (Timer* _timer : allTimers)
	{
		delete _timer;
	}
}

void TimerManager::Update()
{
	for (Timer* _timer : allTimers)
	{
		//_timer->Update();
	}
}

void TimerManager::Pause()
{
	for (Timer* _timer : allTimers)
	{
		_timer->Pause();
	}
}

//Faire la classe timer avec le callback le + générique possible