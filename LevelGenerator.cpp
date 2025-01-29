#include "LevelGenerator.h"
#include "Level.h"
#include "GameManager.h"

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

	GenerateGround();

	for (u_int _y = 0; _y < sizeY; _y+=spaceBetweenElements)
	{
		if (_y + spaceBetweenElements >= sizeY) continue;

		for (u_int _x = 0; _x < sizeX; _x+=spaceBetweenElements)
		{
			if (_x + spaceBetweenElements >= sizeX) continue;

			const float _offsetX = GetRandomNumberInRange<float>(-15.0f, 15.0f);
			const float _offsetY = GetRandomNumberInRange<float>(-15.0f, 15.0f);
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

	// Placer les barbelés autour de la carte
	for (u_int _y = 0; _y <= sizeY + groundTileSize.y; _y += groundTileSize.y)
	{
		for (u_int _x = 0; _x <= sizeX + groundTileSize.x; _x += groundTileSize.x)
		{
			// Vérifier si nous sommes en dehors des limites jouables
			bool isBorder = (_x == 0 || _x == sizeX || _y == 0 || _y == sizeY);
			if (isBorder)
			{
				MeshActor* _barbed = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(90.0f, 90.0f), "Object/Barbed")));
				_barbed->SetPosition(Vector2f((float)(_x - groundTileSize.x), (float)(_y - groundTileSize.y)));
				_barbed->SetOriginAtMiddle();
			}
		}
	}

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

