#include "MeshTest.h"
#include "Tank.h"


MeshTest::MeshTest(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collisions = CreateComponent<CollisionComponent>("Rock", IS_ALL, CT_BLOCK, map<string, CollisionType>{{"Tank", CT_OVERLAP}});
	SetLayer(Layer::LayerType::BREAKABLE);
}

MeshTest::MeshTest(const MeshTest& _other) : MeshActor(_other)
{
	collisions = CreateComponent<CollisionComponent>(*_other.collisions);
}

void MeshTest::OnCollision(const CollisionData& _data)
{
	if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::PLAYER)
		{
			Tank* _tank = Cast<Tank>(_data.other);
			if (!_tank->HasMaxSpeed())
			{
				_tank->ResetSpeed();
			}
		}
	}
}
