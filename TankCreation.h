#pragma once
#include "Track.h"
#include "Weapon.h"
#include "Hull.h"


struct HullsData
{
	vector<string> hullsName;
	map<string, SubclassOf<Hull>> hulls;

	HullsData()
	{
		hullsName =
		{
			"Hull_1",
			"Hull_2",
			"Hull_3",
			"Hull_4",
			"Hull_5",
			"Hull_6",
			"Hull_7",
			"Hull_8",
		};

		Vector2f _size = { 50.0f, 50.0f }; //TODO d�cider taille final
		// _size = taille de la texture * facteur (grossissement ou inverse)

		int _length = CAST(int, hullsName.size());

		for (int _index = 0; _index < _length; _index++)
		{
			Vector2f _size = { 50.0f, 50.0f }; //TODO d�cider taille final
			Hull _hull = Hull(_size, "/Tank/Hulls_1/Hulls_1", PNG, false, IntRect(Vector2i(256 * _index, 0), { 256,256 }));
			SubclassOf<Hull> _hullSubClassOf = SubclassOf<Hull>(_hull);
			hulls.insert({hullsName[_index],_hullSubClassOf});
		}
	}
};

struct WeaponData
{
	vector<string> WeaponsName;
	map<string, SubclassOf<Weapon>> Weapons;

	WeaponData()
	{
		WeaponsName =
		{
			"Weapon_1",
			"Weapon_2",
			"Weapon_3",
			"Weapon_4",
			"Weapon_5",
			"Weapon_6",
			"Weapon_7",
			"Weapon_8",
		};

		
		Vector2f _size = { 20.0f, 40.0f }; //TODO d�cider taille final
		// _size = taille de la texture * facteur (grossissement ou inverse)

		//error possible sur la boucle for par rapport au type
		int _length = CAST(int, WeaponsName.size());

		for (int _index = 0; _index < _length; _index++)
		{
			Vector2f _size = { 50.0f, 50.0f }; //TODO d�cider taille final
			Weapon _weapon = Weapon(_size, "/Tank/Weapons_1/Weapons_1", PNG, false, IntRect(Vector2i(94 * _index, 0 ), { 94,212 }));
			SubclassOf<Weapon> _weaponlSubClassOf = SubclassOf<Weapon>(_weapon);
			Weapons.insert({ WeaponsName[_index],_weaponlSubClassOf});
		}
	}
};


//Cr�ation du tank
//Choisir les �l�ments
class TankCreation
{
	//On fait une map pour chaque �l�ment qu'on va initialiser 
	//avec tous les assets possible
	map<string, Track*> tracks;
	WeaponData WeaponsData;
	HullsData _hullsData;

public:
	TankCreation();

public:
	void CreateTank();

private:
	void LoadTankComponents();
};