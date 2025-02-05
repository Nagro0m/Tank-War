#include "Tree.h"
#include "CollisionComponent.h"
#include "Tank.h"

Tree::Tree(const RectangleShapeData& _data) : MeshActor(_data, "Tree")
{
	SetLayer(Layer::LayerType::BREAKABLE);
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
