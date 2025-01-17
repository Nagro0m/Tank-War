#pragma once
#include "Singleton.h"
#include "Actor.h"

class Game : public Singleton<Game>
{
	RenderWindow window;
	Actor* charm;

public:
	Vector2u GetWindowSize() const
	{
		return window.getSize();
	}
public:
	Game();
	~Game();

private:
	void Start();
	void Update();
	void Stop();

public:
	void Launch();
	void UpdateWindow();
};

