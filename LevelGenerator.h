#pragma once

#include "CoreMinimal.h"
#include "MeshActor.h"
#include "Level.h"
#include "GameManager.h"
#include "CollisionComponent.h"

class Level;
enum CollisionType;

template<typename T = MeshActor>
class LevelElement
{
	int chance;
	vector<LevelElement*> variants;
	T* prefab;
public:
	FORCEINLINE float GetChance() const
	{
		return chance;
	}
	FORCEINLINE MeshActor GetSubclass() const
	{
		return *prefab;
	}
	FORCEINLINE MeshActor* GetPrefab() const
	{
		return prefab;
	}



public:
#pragma region Constructors
	LevelElement(T* _actor, const int _chance)
	{
		prefab = _actor;
		chance = _chance;
		variants = vector<LevelElement*>();
	}

	LevelElement(T* _actor, const int _chance, const vector<LevelElement*>& _variants)
	{
		prefab = _actor;
		chance = _chance;
		variants = _variants;
	}
	/// <summary>
	/// Constructeur pour créer un LevelElement qui servira de sol
	/// </summary>
	LevelElement(MeshActor* _actor, const vector<LevelElement*>& _variants=vector<LevelElement*>())
	{
		prefab = _actor;
		chance = 0;
		variants = _variants;
	}

	LevelElement() = default;
	~LevelElement()
	{
		for (LevelElement* _variant : variants)
		{
			delete _variant;
		}
		delete prefab;
	}
#pragma endregion

public:
	FORCEINLINE bool HasVariants() const
	{
		return variants.size() > 0;
	}
	LevelElement<T>* GetRandomVariant() // Pas de const, ça bloque le return this
	{
		LevelElement* _element = LevelGenerator<T>::GetRandomElement(variants);
		return _element ? _element : this;
	}

};
template<typename T = MeshActor>
class LevelGenerator
{
	u_int sizeX, sizeY;
	vector<MeshActor*> generatedElements;
	vector<LevelElement<T>*> elementsList;
	Level* level;
	u_int spaceBetweenElements;

	LevelElement* ground;
	Vector2u groundTileSize;

public:
	FORCEINLINE void SetGround(LevelElement* _ground, const Vector2u& _groundTileSize)
	{
		ground = _ground;
		groundTileSize = _groundTileSize;
	}

public:
#pragma region Constructors
	LevelGenerator(Level* _level, const u_int& _sizeX, const u_int& _sizeY, const u_int& _spaceBetweenElements)
	{
		level = _level;
		sizeX = _sizeX;
		sizeY = _sizeY;
		elementsList = vector<LevelElement*>();
		spaceBetweenElements = _spaceBetweenElements;
		ground = nullptr;

	}

	LevelGenerator(Level* _level, const u_int& _sizeX, const u_int& _sizeY, const vector<LevelElement<T>*>& _elementsList, const u_int& _spaceBetweenElements)
	{
		level = _level;
		sizeX = _sizeX;
		sizeY = _sizeY;
		elementsList = _elementsList;
		spaceBetweenElements = _spaceBetweenElements;
		ground = nullptr;
	}
	~LevelGenerator()
	{
		for (LevelElement* _element : elementsList)
		{
			delete _element;
		}
		delete ground;
	}
#pragma endregion

#pragma region Methods
public:
	FORCEINLINE void AddGenerableElement(LevelElement<T>* _element)
	{
		elementsList.push_back(_element);
	}

	map<Vector2f, MeshActor*> GenerateMap()
	{
		map<Vector2f, MeshActor*> _map;

		const float _offset = 40.0f;

		GenerateGround();

		for (u_int _y = 0; _y < sizeY; _y += spaceBetweenElements)
		{
			if (_y + spaceBetweenElements >= sizeY) continue;

			for (u_int _x = 0; _x < sizeX; _x += spaceBetweenElements)
			{
				if (_x + spaceBetweenElements >= sizeX) continue;

				const float _offsetX = GetRandomNumberInRange<float>(-_offset, _offset);
				const float _offsetY = GetRandomNumberInRange<float>(-_offset, _offset);
				const Vector2f& _position = Vector2f((float)_x + _offsetX, (float)_y + _offsetY);
				GenerateRandomElement(_position);
			}
		}
		return _map;
	}

private:
	/// <summary>
	/// Checker si un élément est déjà à un endroit
	/// </summary>
	/// <param name="_pos">Coordonnées</param>
	/// <returns>bool</returns>
	bool IsElementOverlap(const Vector2f& _pos) const
	{
		for (MeshActor* _actor : generatedElements)
		{
			if (_actor->GetMesh()->GetShape()->GetDrawable()->getGlobalBounds().contains(_pos)) return true;
		}

		return false;
	}
	bool GenerateRandomElement(const Vector2f& _pos)
	{
		if (IsElementOverlap(_pos)) return false;

		LevelElement<T>* _element = GetRandomElement(elementsList);
		if (!_element) return false;

		MeshActor* _actor = Level::SpawnActor(_element->GetSubclass());
		_actor->SetPosition(_pos);
		_actor->SetOriginAtMiddle();
		generatedElements.push_back(_actor);

		return true;

	}
	void GenerateGround()
	{
		if (!ground) return;

		for (u_int _y = 0; _y < sizeY; _y += groundTileSize.y)
		{
			for (u_int _x = 0; _x < sizeX; _x += groundTileSize.x)
			{
				LevelElement<T>* _groundElement = ground;
				if (_groundElement->HasVariants())
				{
					_groundElement = ground->GetRandomVariant();
				}
				MeshActor* _ground = Level::SpawnActor(_groundElement->GetSubclass());
				_ground->SetPosition(Vector2f((float)_x, (float)_y));
				_ground->SetOriginAtMiddle();
			}
		}

		PlaceBarbedWire();
	}
	int GetRandomDirection()
	{
		const vector<int> _directions =
		{
			0,
			90,
			180
		};
		const int _directionsCount = static_cast<u_short>(_directions.size());
		return _directions[GetRandomNumberInRange(0, _directionsCount - 1)];
	}
	void PlaceBarbedWire()

	{
		vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
		float _barbedWireSize = groundTileSize.x;
		// Placer les barbelés sur les bords
		for (float _x = (-_barbedWireSize / 2); _x < sizeX /*+ _barbedWireSize*/; _x += _barbedWireSize)
		{
			MeshActor* _barbed1 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
			_barbed1->SetPosition(Vector2f(_x, -100));// Haut
			_barbed1->SetOriginAtMiddle();

			MeshActor* _barbed2 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
			_barbed2->SetOriginAtMiddle();
			_barbed2->SetPosition(Vector2f(_x, sizeY - 30));// Bas
		}

		for (float _y = (-_barbedWireSize); _y < sizeY; _y += _barbedWireSize)
		{
			MeshActor* _barbed1 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
			_barbed1->SetPosition(Vector2f(-_barbedWireSize / 4, _y));// Gauche
			_barbed1->Rotate(degrees(90));

			MeshActor* _barbed2 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
			_barbed2->SetPosition(Vector2f(sizeX + _barbedWireSize / 4, _y));// Droite
			_barbed2->Rotate(degrees(90));
		}
	}
	friend LevelElement;

	// On fait un set d'IDs pour pouvoir choisir aléatoirement un élément parmis la liste, histoire de ne pas les faire dans l'ordre du vecteur et maximiser le random
	template<typename T>
	static set<u_int> ComputeSetOfIndex(const vector<T>& _vector)
	{
		set<u_int> _variantsId = set<u_int>();
		for (u_int _i = 0; _i < _vector.size(); _i++)
		{
			_variantsId.insert(_i);
		}
		return _variantsId;
	}

	static LevelElement* GetRandomElement(const vector<LevelElement<T>*>& _vector)
	{
		if (_vector.empty()) return nullptr;

		int _spawnChance = 60; // % de chance qu'un élément spawn

		if (GetRandomNumberInRange(0, 100) > _spawnChance)
			return nullptr; // Aucun élément ne spawn

		// Créer une table cumulative pour les chances
		vector<int> _cumulativeChances;
		int _totalChance = 0;

		for (const LevelElement* _element : _vector)
		{
			_totalChance += _element->GetChance();
			_cumulativeChances.push_back(_totalChance);
		}

		// Tirage aléatoire en fonction de la table cumulative
		const int _random = GetRandomNumberInRange(0, _totalChance - 1);
		const u_int _vectorSize = CAST(u_int, _vector.size());
		for (u_int _index = 0; _index < _vectorSize; ++_index)
		{
			if (_random < _cumulativeChances[_index])
			{
				LevelElement* _element = _vector[_index];
				return _element->HasVariants() ? _element->GetRandomVariant() : _element;
			}
		}
		return nullptr;
	}


#pragma endregion

};

