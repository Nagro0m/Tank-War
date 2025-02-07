#include "Rock.h"
#include "Tank.h"

Rock::Rock(const RectangleShapeData& _data) : MeshActor(_data, "Rock")
{
	SetLayer(Layer::LayerType::BREAKABLE);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	collision->SetInformation("Rock", IS_ALL, CT_BLOCK, false);
	collision->AddResponses(_responsesMesh);
}

Rock::Rock(const CircleShapeData& _data) : MeshActor(_data, "Rock")
{
	SetLayer(Layer::LayerType::BREAKABLE);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	collision->SetInformation("Rock", IS_ALL, CT_BLOCK, false);
	collision->AddResponses(_responsesMesh);
}

Rock::Rock(const Rock& _other) : MeshActor(_other)
{
	SetLayer(_other.GetLayer());
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
