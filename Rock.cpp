#include "Rock.h"
#include "CollisionComponent.h"
#include "Tank.h"

Rock::Rock(const RectangleShapeData& _data) : MeshActor(_data, "Rock")
{
	SetLayer(Layer::LayerType::BREAKABLE);
}

void Rock::BeginPlay()
{
	Super::BeginPlay();
}

void Rock::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Rock::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank && !_tank->HasMaxSpeed())
			{
				_tank->ResetSpeed();
			}
		}
	}
}

void Rock::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank && !_tank->HasMaxSpeed())
			{
				_tank->ResetSpeed();
			}
		}
	}
}

void Rock::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{

		}
	}
}
