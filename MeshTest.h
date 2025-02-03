#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"

class MeshTest : public MeshActor
{
	CollisionComponent* collisions;
public:
	MeshTest(const RectangleShapeData& _data, const string& _name = "MeshTest");
};

