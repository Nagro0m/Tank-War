#pragma once
#include "Track.h"
#include "Weapon.h"
#include "Hull.h"

//Création du tank
//Choisir les éléments
class TankCreation
{
	//On fait une map pour chaque élément qu'on va initialiser 
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