#include "MeshTest.h"

MeshTest::MeshTest(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collisions = CreateComponent<CollisionComponent>(AT_BREAKABLE, CT_OVERLAP, LT_DYNAMIC, set<ActorType>{ AT_BREAKABLE }
	, [&]() {SetToDelete(); });
}

MeshTest::MeshTest(const MeshTest& _other) : MeshActor(_other)
{
	collisions = CreateComponent<CollisionComponent>(*_other.collisions);
}
