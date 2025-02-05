#include "Tree.h"
#include "CollisionComponent.h"
#include "Tank.h"

Tree::Tree(const RectangleShapeData& _data) : MeshActor(_data, "Tree")
{
	SetLayer(Layer::LayerType::BREAKABLE);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	collision = CreateComponent<CollisionComponent>("Tree", IS_ALL, CT_BLOCK);
	collision->AddResponses(_responsesMesh);
}

Tree::Tree(const Tree& _other) : MeshActor(_other)
{
	SetLayer(_other.GetLayer());
	collision = CreateComponent<CollisionComponent>(*_other.collision);
}

void Tree::BeginPlay()
{
	Super::BeginPlay();
}

void Tree::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Tree::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank && !_tank->HasMaxSpeed());
			{
				_tank->ResetSpeed();
			}
		}
	}
}

void Tree::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank && !_tank->HasMaxSpeed());
			{
				_tank->ResetSpeed();
			}
		}
	}
}

void Tree::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{

		}
	}
}
