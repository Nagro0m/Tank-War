#pragma once
#include "MeshActor.h"

class Root : public MeshActor
{
public:
	Root(const RectangleShapeData& _data);

	Root(const Root& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
	virtual Root* Clone() const override { return new Root(*this); }
};

