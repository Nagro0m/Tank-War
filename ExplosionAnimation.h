#pragma once
#include "MeshActor.h"
#include "AnimationComponent.h"

class ExplosionAnimation : public MeshActor
{
	AnimationComponent* animation;

public:
	ExplosionAnimation(const RectangleShapeData& _data);
	ExplosionAnimation(const ExplosionAnimation& _other);

	virtual void Construct() override;

	virtual void RenderMesh(RenderWindow& _window) override;

	virtual void Deconstruct() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
};

