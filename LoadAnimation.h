#pragma once
#include "MeshActor.h"
#include "AnimationComponent.h"

class LoadAnimation : public MeshActor
{
	AnimationComponent* animation;

public:
	LoadAnimation(const RectangleShapeData& _data);
	LoadAnimation(const LoadAnimation& _other);

	virtual void Construct() override;

	virtual void RenderMesh(RenderWindow& _window) override;

	virtual void Deconstruct() override;

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
};

