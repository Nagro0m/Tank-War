#pragma once
#include "Game.h"


class Tank;

class FuelGameplay : public Game
{
	Tank* player1Tank;
public:
	FuelGameplay();
	~FuelGameplay();

	virtual void Start() override;
	virtual bool Update() override;
	virtual void Stop() override;
};

