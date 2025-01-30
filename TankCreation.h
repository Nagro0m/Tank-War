#pragma once
#include "Level.h"
#include "Track.h"
#include "Weapon.h"
#include "Hull.h"

namespace Tank
{
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

			//Vector2f _size = { 50.0f, 50.0f }; //TODO décider taille final
			// _size = taille de la texture * facteur (grossissement ou inverse)

			int _length = CAST(int, hullsName.size());

			for (int _index = 0; _index < _length; _index++)
			{
				Vector2f _size = { 50.0f, 50.0f }; //TODO décider taille final
				Hull _hull = Hull(_size, "/Tank/Hulls_1/Hulls_1", PNG, false, IntRect(Vector2i(256 * _index, 0), { 256,256 }));
				SubclassOf<Hull> _hullSubClassOf = SubclassOf<Hull>(_hull);
				hulls.insert({ hullsName[_index],_hullSubClassOf });
			}
		}
	};

	struct WeaponsData
	{
	private:
		vector<string> weaponsName;
		map<string, SubclassOf<Weapon>> weapons;

	public:

		WeaponsData()
		{
			weaponsName =
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


			//Vector2f _size = { 20.0f, 40.0f }; //TODO décider taille final
			// _size = taille de la texture * facteur (grossissement ou inverse)

			//error possible sur la boucle for par rapport au type
			int _length = CAST(int, weaponsName.size());

			for (int _index = 0; _index < _length; _index++)
			{
				Vector2f _size = { 50.0f, 50.0f }; //TODO décider taille final
				Weapon _weapon = Weapon(_size, "/Tank/Weapons_1/Weapons_1", PNG, false, IntRect(Vector2i(94 * _index, 0), { 94,212 }));
				SubclassOf<Weapon> _weaponlSubClassOf = SubclassOf<Weapon>(_weapon);
				weapons.insert({ weaponsName[_index],_weaponlSubClassOf });
			}
		}

		//obtenir la liste des noms d'armes
		const vector<string>& GetWeaponsName() const
		{
			return weaponsName;
		}

		// Accesseur pour récupérer une arme spécifique
		const SubclassOf<Weapon>* GetWeapon(const string& _weaponName) const
		{
			auto _it = weapons.find(_weaponName);
			if (_it != weapons.end())
			{
				return &_it->second;
			}
			return nullptr; // Retourne nullptr si l'arme n'existe pas
		}

		// Vérifie si une arme existe
		bool HasWeapon(const string& _weaponName) const
		{
			return weapons.find(_weaponName) != weapons.end();
		}
	};


	//Création du tank
	//Choisir les éléments
	class TankCreation
	{
		//On fait une map pour chaque élément qu'on va initialiser 
		//avec tous les assets possible
		map<string, Track*> tracks;
		WeaponsData weaponsData;
		HullsData hullsData;
		vector<MeshActor*> creationMenu;

	public:
		TankCreation();

	public:
		void CreateTank();

		void DisplayWeaponSprite(const SubclassOf<Weapon>& _weapon, const Vector2f& _position);

		void HandleWeaponSelection(int& _currentWeaponIndex, const vector<string>& _weaponsName);

	private:
		void LoadTankComponents();

		MeshActor* CreateActors(const Vector2f& _size, const string& _texture, const Vector2f& _position,
			bool _useMiddleOrigin = true, float _rotation = 0.0f)
		{
			MeshActor* _actor = Level::SpawnActor(MeshActor(RectangleShapeData(_size, _texture)));

			if (_useMiddleOrigin)
			{
				_actor->SetOriginAtMiddle();
			}
			_actor->SetPosition(_position);
			if (_rotation != 0.0f)
			{
				_actor->Rotate(degrees(_rotation));
			}
			return _actor;
		}
	};
}