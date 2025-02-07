#pragma once
#include "MeshActor.h"

class CollisionComponent;

class BarbedWire : public MeshActor
{
	//CollisionComponent* collision;
public:
	BarbedWire(const RectangleShapeData& _data);

	BarbedWire(const BarbedWire& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
};

