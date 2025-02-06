#include "BarbedWire.h"
#include "Tank.h"

BarbedWire::BarbedWire(const RectangleShapeData& _data) : MeshActor(_data, "BarbedWire")
{
	SetLayer(Layer::LayerType::WORLD_STATIC);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	collision->SetInformation("BardedWire", IS_ALL, CT_BLOCK, false);
	collision->AddResponses(_responsesMesh);
}

BarbedWire::BarbedWire(const BarbedWire& _other) : MeshActor(_other)
{
	SetLayer(_other.GetLayer());
}


void BarbedWire::BeginPlay()
{
	Super::BeginPlay();
}

void BarbedWire::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void BarbedWire::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank)
			{
				_tank->ResetSpeed();
			}
		}
	}
}

void BarbedWire::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (_tank)
			{
				_tank->ResetSpeed();
			}
		}
	}
}

void BarbedWire::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{

		}
	}
}
