#pragma once
#include "Track.h"
#include "Weapon.h"
#include "Hull.h"

//Cr�ation du tank
//Choisir les �l�ments
class TankCreation
{
	//On fait une map pour chaque �l�ment qu'on va initialiser 
	//avec tous les assets possible
	map<string, Track*> tracks;
	map<string, Weapon*> Weapon;
	map<string, Hull*> Hull;

public:
	TankCreation();

public:
	void CreateTank();

private:
	void LoadTankComponents();
};