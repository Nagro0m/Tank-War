#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"

class MeshTest : public MeshActor
{
	CollisionComponent* collision;
public:
	FORCEINLINE CollisionComponent* GetCollision() const
	{
		return collision;
	}


	MeshTest(const RectangleShapeData& _data, const string& _name = "MeshTest");
	MeshTest(const MeshTest& _other);


	virtual void OnCollision(const CollisionData& _data) override;

};

