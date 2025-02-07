#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"


class Bullet : public MeshActor
{
	Vector2f direction;
	MovementComponent* movement;

public:
	Bullet(const Vector2f& _direction);
	Bullet(const Bullet& _other);

public:
	virtual void Tick(const float _deltaTime) override;

	void Construct();
	void Deconstruct();
	void BeginPlay();

public:
	void Explosion();
};