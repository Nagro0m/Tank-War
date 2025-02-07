#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

class Bullet : public MeshActor
{
	Vector2f direction;
	MovementComponent* movement;
	bool isExplode;
	int explosionNumber;

public:
	FORCEINLINE CollisionComponent* GetCollision() const
	{
		return collision;
	}
public:
	Bullet(const Vector2f& _direction);
	Bullet(const Bullet& _other);

public:
	virtual void Tick(const float _deltaTime) override;

	void Construct();
	void Deconstruct();
	void BeginPlay();

	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;

public:
	void Explosion();
};