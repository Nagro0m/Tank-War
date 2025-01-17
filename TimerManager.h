#pragma once
#include "Singleton.h"
#include "Game.h"

using Seconds = float;
using MilliSec = int32_t;
using MicroSec = int64_t;

template <typename DurationType>
class Timer;

template <typename DurationType = MilliSec>
class TimerManager : public Singleton<TimerManager<DurationType>>
{
	using T = Timer<DurationType>;
	friend T;

#pragma region Var Membres
	// Objet qui contient toutes les données de temps
	Clock clock;
	// Temps en miliseconde depuis le début du prog
	DurationType time;
	// Stocke temporairement la précédente durée de la frame
	DurationType lastTime;
	// Mettre à jours le content de FPS
	DurationType lastFrameTime;
	// Temps depuis la dernière image rendu 
	DurationType elapsedTime;
	// Temps depuis la dernière image rendu avec le timeScale
	DurationType deltaTime;
	// Vitesse à laquelle le temps s'écoule
	DurationType timeScale;
	// NB image rendu depuis le début
	u_llong framesCount;
	// MAximum d'image rendu par seconde
	u_short maxFrameRate;
	// Nombre d'image rendu par seconde
	DurationType fps;
	// Collection de tous les time existant
	set<T*> allTimers;

	map<type_index, DurationType> durations;
#pragma endregion

private:
	FORCEINLINE DurationType GetDuration() const
	{
		return durations.at(typeid(DurationType));
	}

public:
	FORCEINLINE set<T*> GetAllTimers() const
	{
		return allTimers;
	}

	FORCEINLINE void AddTimer(T* _timer)
	{
		allTimers.insert(_timer);
	}

	FORCEINLINE void RemoveTimer(T* _timer)
	{
		allTimers.erase(_timer);
		delete _timer;
	}
	FORCEINLINE void SetTimerScale(const DurationType& _timeScale)
	{
		timeScale = _timeScale;
	}
	FORCEINLINE DurationType ComputeFPS() const
	{
		return GetDuration() / (time - lastFrameTime);
	}

	FORCEINLINE Time GetDeltaTime() const
	{
		return Time(seconds(deltaTime * GetDuration()));
	}
	FORCEINLINE string GetElapsedTime() const
	{
		Time _elapsed = clock.getElapsedTime();
		int _totalSeconds = static_cast<int>(_elapsed.asSeconds());

		int _hours = (_totalSeconds / 3600) % 24; // Nombre d'heures
		int _minutes = (_totalSeconds / 60) % 60; // Nombre de minutes
		int _seconds = _totalSeconds % 60;        // Nombre de secondes

		return string(to_string(_hours) + ":" + to_string(_minutes) + ":" + to_string(_seconds));
	}
	FORCEINLINE string GetTime() const
	{
		auto now = chrono::system_clock::now();
		time_t timeT = chrono::system_clock::to_time_t(now);
		tm localTime;
		localtime_s(&localTime, &timeT);

		char _buffer[9];
		strftime(_buffer, sizeof(_buffer), "%H:%M:%S", &localTime);

		return string(_buffer);
	}

public:
	TimerManager()
	{
		clock.restart();

		clock = Clock();
		time = DurationType();
		lastTime = DurationType();
		lastFrameTime = DurationType();
		elapsedTime = DurationType();
		deltaTime = DurationType();
		timeScale = 1.0f;
		framesCount = 0;
		maxFrameRate = 50;
		fps = DurationType();
		allTimers = set<T*>();

		durations =
		{
			{typeid(Seconds), 1},
			{typeid(MilliSec), 1000},
			{typeid(MicroSec), 1000000},
		};
	}
	~TimerManager()
	{
		for (T* _timer : allTimers)
		{
			delete _timer;
		}
	}

public:

	void Update()
	{
		for (T* _timer : allTimers)
		{
			if (_timer->IsRunning())
			{
				_timer->Update(deltaTime);
			}
			else return;
		}

		lastTime = time;

		time = GetTime(clock.getElapsedTime());
		elapsedTime = time - lastTime;
		framesCount++;
		deltaTime = elapsedTime * timeScale;

		if (lastFrameTime == 0 || time - lastFrameTime >= maxFrameRate)
		{
			lastFrameTime = time;
			Game::GetInstance().UpdateWindow();
		}

		using Iterator = set<Timer<Seconds>*>::iterator;
		for (Iterator _iterator = allTimers.begin(); _iterator != allTimers.end();)
		{
			T* _timer = *_iterator;
			_timer->Update(deltaTime);
			if (_timer->IsToDelete())
			{
				RemoveTimer(_timer);
				_iterator--;
				continue;
			}
			_iterator++;
		}
	}
	void Pause()
	{
		for (T* _timer : allTimers)
		{
			_timer->Pause();
		}
	}

private:
	FORCEINLINE DurationType GetTime(const Time& _time) const
	{
		map<type_index, function<DurationType()>> _durationCallback =
		{
			{typeid(Seconds), [&]() { return _time.asSeconds(); }},
			{typeid(MilliSec), [&]() { return _time.asMilliseconds(); }},
			{typeid(MicroSec), [&]() { return _time.asMicroseconds(); }}

		};
		return _durationCallback[typeid(DurationType)]();
	}

};

using TM_Seconds = TimerManager<Seconds>;
using TM_Milli = TimerManager<MilliSec>;
using TM_Micro = TimerManager<MicroSec>;

template <typename DurationType = MilliSec>
class Timer
{
	DurationType currentTime;
	DurationType duration;
	bool isRunning;
	bool isLoop;
	bool isToDelete;
	function<void()> callback;

public:
	FORCEINLINE bool IsRunning() const
	{
		return isRunning;
	}

	FORCEINLINE bool IsLoop() const
	{
		return isLoop;
	}	
	
	FORCEINLINE bool IsToDelete() const
	{
		return isToDelete;
	}

	FORCEINLINE DurationType GetCurrentTime() const
	{
		return currentTime;
	}

public:
	Timer(const function<void()>& _callback, const Time& _time, const bool _startRunning = false,
		const bool _isLoop = false)
	{
		isRunning = _startRunning;
		isLoop = _isLoop;
		isToDelete = false;
		currentTime = 0;
		duration = TimerManager<DurationType>::GetInstance().GetTime(_time);
		callback = _callback;
		TimerManager<DurationType>::GetInstance().AddTimer(this);
	}

public:

	void Start()
	{
		Reset();
		Resume();
	}
	void Update(const DurationType _deltaTime)
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
	void Stop()
	{
		isToDelete = true;
	}
	void Resume()
	{
		isRunning = true;
	}
	void Reset()
	{
		currentTime = 0.0;
	}
	void Pause()
	{
		isRunning = !isRunning;
	}

};