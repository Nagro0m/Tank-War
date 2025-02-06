#pragma once
#include "MeshActor.h"
#include "AnimationComponent.h"

class ShootAnimation : public MeshActor
{
	AnimationComponent* animation;

public:
	ShootAnimation(const RectangleShapeData& _data);
	ShootAnimation(const ShootAnimation& _other);

	virtual void Construct() override;
	
	virtual void RenderMesh(RenderWindow& _window) override;
	
	virtual void Deconstruct() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
};

