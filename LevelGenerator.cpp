#include "LevelGenerator.h"
#include "Level.h"
#include "GameManager.h"

LevelElement::LevelElement(SubclassOf<MeshActor>* _actor, const int _chance)
{
	prefab = _actor;
	chance = _chance;
	variants = vector<LevelElement*>();
}

LevelElement::LevelElement(SubclassOf<MeshActor>* _actor, const int _chance, const vector<LevelElement*>& _variants)
{
	prefab = _actor;
	chance = _chance;
	variants = _variants;
}
LevelElement::LevelElement(SubclassOf<MeshActor>* _actor, const vector<LevelElement*>& _variants)
{
	prefab = _actor;
	chance = -1.0f;
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

	GenerateGround();
	for (u_int _y = 0; _y < sizeY; _y+=spaceBetweenElements)
	{
		for (u_int _x = 0; _x < sizeX; _x+=spaceBetweenElements)
		{
			GenerateRandomElement(Vector2f((float)_x, (float)_y));
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

	MeshActor* _actor = level->SpawnActor(_element->GetSubclass());
	_actor->SetPosition(_pos);
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
		}
	}
}

