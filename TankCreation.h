#pragma once
#include "Level.h"
#include "Track.h"
#include "Weapon.h"
#include "Hull.h"


//TODO maybe pas trop propre déplacer les fonction utilisant dans cpp / et forward dcp
#include "CameraManager.h"
#include "ActorManager.h"

namespace Tank
{
	struct HullsData
	{
		vector<string> hullsName;
		map<string, shared_ptr<Hull>> hulls;

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

			int _length = static_cast<int>(hullsName.size());

			for (int _index = 0; _index < _length; _index++)
			{
				Vector2f _size = { 200.0f, 200.0f }; // Taille par défaut (modifiable)

				// Création de l'arme
				auto _hullPtr = make_shared<Hull>
					(
						_size, "/Tank/Hulls_1/Hulls_1", PNG, false,
						IntRect(Vector2i(256 * _index, 0), { 256, 256 })
					);

				hulls.insert({ hullsName[_index], _hullPtr });
			}
		}

		// Obtenir la liste des noms d'armes
		const vector<string>& GetHullsName() const
		{
			return hullsName;
		}

		// Récupérer une arme spécifique
		shared_ptr<Hull> GetHull(const string& _hullName) const
		{
			auto _it = hulls.find(_hullName);
			return (_it != hulls.end()) ? _it->second : nullptr;
		}

		// Vérifie si une arme existe
		bool HasHull(const string& _hullName) const
		{
			return hulls.find(_hullName) != hulls.end();
		}
	};

	struct WeaponsData {
	private:
		vector<string> weaponsName;
		map<string, shared_ptr<Weapon>> weapons;

	public:
		WeaponsData() {
			weaponsName = 
			{
				"Weapon_1", "Weapon_2", "Weapon_3", "Weapon_4",
				"Weapon_5", "Weapon_6", "Weapon_7", "Weapon_8"
			};

			int _length = static_cast<int>(weaponsName.size());

			for (int _index = 0; _index < _length; _index++) 
			{
				Vector2f _size = { 50.0f, 100.0f }; // Taille par défaut (modifiable)

				// Création de l'arme
				auto _weaponPtr = make_shared<Weapon>
				(
					_size, "/Tank/Weapons_1/Weapons_1", PNG, false,
					IntRect(Vector2i(94 * _index, 0), { 94, 212 })
				);

				weapons.insert({ weaponsName[_index], _weaponPtr });
			}
		}

		~WeaponsData() {
			for (const auto& _weapon : weapons) 
			{
				if (_weapon.second) {
					M_ACTOR.RemoveActor(_weapon.second.get());
				}
			}
		}

		// Obtenir la liste des noms d'armes
		const vector<string>& GetWeaponsName() const 
		{
			return weaponsName;
		}

		// Récupérer une arme spécifique
		shared_ptr<Weapon> GetWeapon(const string& _weaponName) const 
		{
			auto _it = weapons.find(_weaponName);
			return (_it != weapons.end()) ? _it->second : nullptr;
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
		map<string, MeshActor*> creationMenu;
		//CameraActor* cameraCreationMenu;
		shared_ptr<Weapon> currentWeapon;
		int currentWeaponIndex;
		shared_ptr<Hull> currentHull;
		shared_ptr<class TankActor> tank;
	public:
		TankCreation();

	public:
		void CreateTank();

		void SetupInputBindings();

		void UpdateWeaponSelection();

		void RefreshWeaponDisplay();

		void Update();

		Tank::TankActor* LoadTankComponents();

	private:
		void GenerateTankCreationMenu();

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