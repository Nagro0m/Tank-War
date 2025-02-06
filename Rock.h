#pragma once
#include "MeshActor.h"

class Rock : public MeshActor
{
public:
	Rock(const RectangleShapeData& _data);

	Rock(const float _size, const string& _path);

	Rock(const Rock& _other);

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
	virtual Rock* Clone() const override { return new Rock(*this); }

};

