#pragma once

#include "CoreMinimal.h"
#include "MeshActor.h"
#include "Level.h"
#include "GameManager.h"
#include "CollisionComponent.h"

class Level;
enum CollisionType;

template<typename T = MeshActor>
class LevelGenerator;

template<typename T = MeshActor>
class LevelElement
{
	int chance;
	vector<LevelElement<T>*> variants;
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

	FORCEINLINE bool HasVariants() const
	{
		return !variants.empty();
	}

	LevelElement<T>* GetRandomVariant()
	{
		LevelElement<T>* _element = LevelGenerator<T>::GetRandomElement(variants);
		return _element ? _element : this;
	}

#pragma region Constructors
	LevelElement(T* _actor, int _chance)
		: prefab(_actor), chance(_chance), variants() {}

	LevelElement(T* _actor, int _chance, const vector<LevelElement<T>*>& _variants)
		: prefab(_actor), chance(_chance), variants(_variants) {}

	LevelElement(MeshActor* _actor, const vector<LevelElement<T>*>& _variants = {})
		: prefab(_actor), chance(0), variants(_variants) {}

	~LevelElement()
	{
		for (auto _variant : variants)
		{
			delete _variant;
		}
		delete prefab;
	}
#pragma endregion
};
template<typename T>
class LevelGenerator
{
    u_int sizeX, sizeY;
    vector<MeshActor*> generatedElements;
    vector<LevelElement<MeshActor>*> elementsList;  // Stocker des LevelElement<MeshActor>*
    Level* level;
    u_int spaceBetweenElements;

    LevelElement<MeshActor>* ground;
    Vector2u groundTileSize;

public:
    FORCEINLINE void SetGround(LevelElement<MeshActor>* _ground, const Vector2u& _groundTileSize)
    {
        ground = _ground;
        groundTileSize = _groundTileSize;
    }

    LevelGenerator(Level* _level, u_int _sizeX, u_int _sizeY, u_int _spaceBetweenElements)
        : level(_level), sizeX(_sizeX), sizeY(_sizeY), spaceBetweenElements(_spaceBetweenElements), ground(nullptr)
    {}

    ~LevelGenerator()
    {
        for (auto _element : elementsList)
        {
            delete _element;
        }
        delete ground;
    }

    FORCEINLINE void AddGenerableElement(LevelElement<MeshActor>* _element)
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
                const Vector2f _position((float)_x + _offsetX, (float)_y + _offsetY);
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

        LevelElement<MeshActor>* _element = GetRandomElement(elementsList);
        if (!_element) return false;

        // Vérifier si l'élément a des variantes et choisir une variante aléatoire
        if (_element->HasVariants())
        {
            _element = _element->GetRandomVariant();
        }

        T* _actor = Level::SpawnActor<T>(_element->GetPrefab());
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
                // Utilisation de la variante aléatoire si elle existe
                LevelElement<MeshActor>* _groundElement = ground;
                if (_groundElement->HasVariants())
                {
                    _groundElement = _groundElement->GetRandomVariant();
                }

                // Spawner l'élément au bon endroit
                T* _actor = Level::SpawnActor<T>(_groundElement->GetPrefab());
                _actor->SetPosition(Vector2f((float)_x, (float)_y));
                _actor->SetOriginAtMiddle();
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

    static LevelElement<MeshActor>* GetRandomElement(const vector<LevelElement<MeshActor>*>& _vector)
    {
        if (_vector.empty()) return nullptr;

        int _spawnChance = 60; // % de chance qu'un élément spawn
        if (GetRandomNumberInRange(0, 100) > _spawnChance)
            return nullptr; // Aucun élément ne spawn...

        // Choisir un élément au hasard dans le vecteur
        return _vector[GetRandomNumberInRange(0, _vector.size() - 1)];
    }
};