#pragma once
#include "MeshActor.h"

class Hull : public MeshActor
{
public:
	Hull();

public:
	void Move(const Vector2f _newPosition);
};