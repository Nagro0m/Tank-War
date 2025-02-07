#pragma once
#include "Level.h"


class Tank;

class FuelModeLevel : public Level
{
	Tank* player1Tank;
	RenderWindow window;

public:
	FuelModeLevel();
	~FuelModeLevel();

	virtual void Load();
	virtual void Unload();

protected:
	virtual void InitLevel();
};

