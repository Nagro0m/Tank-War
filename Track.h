#pragma once
#include "MeshActor.h"
#include "AnimationComponent.h"

class Track : public MeshActor
{
	AnimationComponent* animation;
	bool isMoving;

public:
	void SetIsMoving()
	{
		isMoving = !isMoving;
		if (isMoving) animation->SetCurrentAnimation("Moving");
		else animation->SetCurrentAnimation("Idle");

		animation->StartAnimation();
	}

public:
	Track(const Vector2f& _size, const string& _path);
	Track(const Track& _other);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
};
