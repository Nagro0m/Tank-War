#pragma once

#include "CoreMinimal.h"
#include "MeshActor.h"

class Level;

class LevelElement
{
	int chance;
	vector<LevelElement*> variants;
	MeshActor* prefab;
public:
	FORCEINLINE float GetChance() const
	{
		return chance;
	}
	FORCEINLINE MeshActor GetSubclass() const
	{
		return *prefab;
	}

public:
#pragma region Constructors
	LevelElement(MeshActor* _actor, const int _chance);
	LevelElement(MeshActor* _actor, const int _chance, const vector<LevelElement*>& _variants);
	/// <summary>
	/// Constructeur pour créer un LevelElement qui servira de sol
	/// </summary>
	LevelElement(MeshActor* _actor, const vector<LevelElement*>& _variants=vector<LevelElement*>());
	LevelElement() = default;
	~LevelElement();
#pragma endregion

public:
	FORCEINLINE bool HasVariants() const
	{
		return variants.size() > 0;
	}
	LevelElement* GetRandomVariant(); // Pas de const, ça bloque le return this

};

class LevelGenerator
{
	u_int sizeX, sizeY;
	vector<MeshActor*> generatedElements;
	vector<LevelElement*> elementsList;
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
	LevelGenerator(Level* _level, const u_int& _sizeX, const u_int& _sizeY, const u_int& _spaceBetweenElements);
	LevelGenerator(Level* _level, const u_int& _sizeX, const u_int& _sizeY, const vector<LevelElement*>& _elementsList, const u_int& _spaceBetweenElements);
	~LevelGenerator();
#pragma endregion

#pragma region Methods
public:
	FORCEINLINE void AddGenerableElement(LevelElement* _element)
	{
		elementsList.push_back(_element);
	}

	map<Vector2f, MeshActor*> GenerateMap();

private:
	/// <summary>
	/// Checker si un élément est déjà à un endroit
	/// </summary>
	/// <param name="_pos">Coordonnées</param>
	/// <returns>bool</returns>
	bool IsElementOverlap(const Vector2f& _pos) const;
	bool GenerateRandomElement(const Vector2f& _pos);
	void GenerateGround();
	int GetRandomDirection();
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

	static LevelElement* GetRandomElement(const vector<LevelElement*>& _vector)
	{
		set<u_int> _variantsId = ComputeSetOfIndex(_vector);

		while (!_variantsId.empty())
		{
			const u_int& _id = GetRandomNumberInRange(0, static_cast<u_int>(_variantsId.size() - 1));
			const int _random = GetRandomNumberInRange(0, 100);
			if (_random <= _vector[_id]->GetChance())
			{
				LevelElement* _element = _vector[_id];
				if (!_element->HasVariants()) return _element;
				return _element->GetRandomVariant();
			}
			_variantsId.erase(_id);
		}

		return nullptr;
	}
#pragma endregion

};

