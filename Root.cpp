#include "Root.h"
#include "Tank.h"

Root::Root(const RectangleShapeData& _data) : MeshActor(_data, "Root")
{
	SetLayer(Layer::LayerType::WORLD_DYNAMIC);
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	collision->SetInformation("Root", IS_ALL, CT_NONE, false);
	collision->AddResponses(_responsesMesh);
}

Root::Root(const Root& _other) : MeshActor(_other)
{
	SetLayer(_other.GetLayer());;
}

void Root::BeginPlay()
{
	Super::BeginPlay();
}

void Root::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void Root::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
/*		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if(_tank && !_tank->HasMaxSpeed())
			{
				_tank->ResetSpeed();
			}
		}*/
	}
}

void Root::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{

		}
	}
}

void Root::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{

		}
	}
}
