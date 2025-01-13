#pragma once
#include "Singleton.h"
#include "Actor.h"

class Game : public Singleton<Game>
{
	RenderWindow window;
	Actor* charm;

public:
	Game();
	~Game();

private:
	void Start();
	void Update();
	void UpdateWindow();
	void Stop();

public:
	void Launch();
};

