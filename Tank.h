#pragma once
#include "Hull.h"
#include "Weapon.h"
#include "Track.h"

class Tank
{
	//Corps du tank
	Hull* hull;
	//Canon
	Weapon* weapon;
	//Chenilles
	Track* track;

	int life;
	bool isMoving;

public:
	Tank();
	~Tank();
};