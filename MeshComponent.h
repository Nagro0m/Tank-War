#pragma once
#include "Component.h"
#include "Actor.h"

class MeshComponent : public Component
{
	ShapeObject* shape;

public:
	FORCEINLINE ShapeObject* GetShape() const
	{
		return shape;
	}

	FORCEINLINE void SetShape(ShapeObject* _shape)
	{
		shape = _shape;
	}

public:
	MeshComponent(Actor* _owner, const float _radius = 0.0f, const string& _path = "",
		const size_t& _pointCount = 30, const IntRect& _rect = IntRect());

	MeshComponent(Actor* _owner, const Vector2f& _size, const string& _path = "", const IntRect& _rect = IntRect());
	~MeshComponent();
};

