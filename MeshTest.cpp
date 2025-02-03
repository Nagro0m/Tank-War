#include "MeshTest.h"

MeshTest::MeshTest(const RectangleShapeData& _data, const string& _name) : MeshActor(_data, _name)
{
	collisions = CreateComponent<CollisionComponent>(AT_BREAKABLE, CT_OVERLAP, LT_DYNAMIC, set<ActorType>{ AT_BREAKABLE }
	, [&]() {LOG(Display, "Mesh_collision"); });
}
