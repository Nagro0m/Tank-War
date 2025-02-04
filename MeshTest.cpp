#include "MeshTest.h"
#include "Tank.h"


MeshTest::MeshTest(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collision = CreateComponent<CollisionComponent>("Rock", IS_ALL, CT_BLOCK);
	SetLayer(Layer::LayerType::BREAKABLE);
}

MeshTest::MeshTest(const MeshTest& _other) : MeshActor(_other)
{
	collision = CreateComponent<CollisionComponent>(*_other.collision);
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
