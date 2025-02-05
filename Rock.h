#pragma once
#include "MeshActor.h"

class CollisionComponent;

class Rock : public MeshActor
{
	CollisionComponent* collision;
public:
	Rock(const RectangleShapeData& _data);

	Rock(const Rock& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
};

