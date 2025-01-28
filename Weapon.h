#pragma once
#include "MeshActor.h"
#include "AnimationComponent.h"

class Weapon : public MeshActor
{
	MeshActor* Shoot;
	Animation* animation;

public:
	Weapon();
public:
	void Move(const Vector2f _newPosition);
};

