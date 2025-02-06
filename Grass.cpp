#include "Grass.h"
#include "Tank.h"

Grass::Grass(const RectangleShapeData& _data) : MeshActor(_data, "Grass")
{
	SetLayer(Layer::LayerType::BREAKABLE);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	collision->SetInformation("Grass", IS_ALL, CT_BLOCK, false);
	collision->AddResponses(_responsesMesh);
}

Grass::Grass(const Grass& _other) : MeshActor(_other)
{
	SetLayer(_other.GetLayer());
}

void Grass::BeginPlay()
{
	Super::BeginPlay();
}

void Grass::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Grass::CollisionEnter(const CollisionData& _data)
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

void Grass::CollisionUpdate(const CollisionData& _data)
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

void Grass::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{

		}
	}
}
