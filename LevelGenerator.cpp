#include "LevelGenerator.h"
#include "Level.h"
#include "GameManager.h"
#include "CollisionComponent.h"

LevelElement::LevelElement(MeshActor* _actor, const int _chance)
{
	prefab = _actor;
	chance = _chance;
	variants = vector<LevelElement*>();
}

LevelElement::LevelElement(MeshActor* _actor, const int _chance, const vector<LevelElement*>& _variants)
{
	prefab = _actor;
	chance = _chance;
	variants = _variants;
}

LevelElement::LevelElement(MeshActor* _actor, const vector<LevelElement*>& _variants)
{
	prefab = _actor;
	chance = 0;
	variants = _variants;
}

LevelElement::~LevelElement()
{
	for (LevelElement* _variant : variants)
	{
		delete _variant;
	}
	delete prefab;
}

LevelElement* LevelElement::GetRandomVariant()
{
	LevelElement* _element = LevelGenerator::GetRandomElement(variants);
	return _element ? _element : this;
}

LevelGenerator::LevelGenerator(Level* _level, const u_int& _sizeX, const u_int& _sizeY, const u_int& _spaceBetweenElements)
{
	level = _level;
	sizeX = _sizeX;
	sizeY = _sizeY;
	elementsList = vector<LevelElement*>();
	spaceBetweenElements = _spaceBetweenElements;
	ground = nullptr;

}

LevelGenerator::LevelGenerator(Level* _level, const u_int& _sizeX, const u_int& _sizeY, const vector<LevelElement*>& _elementsList, const u_int& _spaceBetweenElements)
{
	level = _level;
	sizeX = _sizeX;
	sizeY = _sizeY;
	elementsList = _elementsList;
	spaceBetweenElements = _spaceBetweenElements;
	ground = nullptr;
}

LevelGenerator::~LevelGenerator()
{
	for (LevelElement* _element : elementsList)
	{
		delete _element;
	}
	delete ground;
}

map<Vector2f, MeshActor*> LevelGenerator::GenerateMap()
{
	map<Vector2f, MeshActor*> _map;

	const float _offset = 40.0f;

	GenerateGround();

	for (u_int _y = 0; _y < sizeY; _y+=spaceBetweenElements)
	{
		if (_y + spaceBetweenElements >= sizeY) continue;

		for (u_int _x = 0; _x < sizeX; _x+=spaceBetweenElements)
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

bool LevelGenerator::IsElementOverlap(const Vector2f& _pos) const
{
	for (MeshActor* _actor : generatedElements)
	{
		if (_actor->GetMesh()->GetShape()->GetDrawable()->getGlobalBounds().contains(_pos)) return true;
	}

	return false;
}

bool LevelGenerator::GenerateRandomElement(const Vector2f& _pos)
{
	if (IsElementOverlap(_pos)) return false;

	LevelElement* _element = GetRandomElement(elementsList);
	if (!_element) return false;

	MeshActor* _actor = Level::SpawnActor(_element->GetSubclass());
	_actor->SetPosition(_pos);
	_actor->SetOriginAtMiddle();
	generatedElements.push_back(_actor);

	return true;

}

void LevelGenerator::GenerateGround()
{
	if (!ground) return;

	for (u_int _y = 0; _y < sizeY; _y += groundTileSize.y)
	{
		for (u_int _x = 0; _x < sizeX; _x += groundTileSize.x)
		{
			LevelElement* _groundElement = ground;
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

int LevelGenerator::GetRandomDirection()
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

void LevelGenerator::PlaceBarbedWire()
{
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	float _barbedWireSize = groundTileSize.x;
	// Placer les barbelés sur les bords
	for (float _x = (-_barbedWireSize /2); _x < sizeX /*+ _barbedWireSize*/; _x += _barbedWireSize)
	{
		MeshActor* _barbed1 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
		_barbed1->SetPosition(Vector2f(_x , -100));// Haut
		_barbed1->SetOriginAtMiddle();

		MeshActor* _barbed2 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
		_barbed2->SetOriginAtMiddle();
		_barbed2->SetPosition(Vector2f(_x , sizeY - 30));// Bas
	}

	for (float _y = (-_barbedWireSize); _y < sizeY; _y += _barbedWireSize)
	{
		MeshActor* _barbed1 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
		_barbed1->SetPosition(Vector2f(-_barbedWireSize / 4, _y ));// Gauche
		_barbed1->Rotate(degrees(90));

		MeshActor* _barbed2 = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(_barbedWireSize, _barbedWireSize), "Object/Barbed")));
		_barbed2->SetPosition(Vector2f(sizeX + _barbedWireSize/4, _y));// Droite
		_barbed2->Rotate(degrees(90));
	}
}
