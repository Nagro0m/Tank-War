#pragma once
#include "MeshActor.h"

class Grass : public MeshActor
{
public:
	Grass(const RectangleShapeData& _data);

	Grass(const Grass& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;

};

