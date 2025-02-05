#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"


class Bullet : public MeshActor
{
	Vector2f direction;

public:
	Bullet(const Vector2f& _direction);

public:
	virtual void Tick(const float _deltaTime) override;

	void Construct();
	void Deconstruct();
	void BeginPlay();
};