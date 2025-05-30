#pragma once
#include "Component.h"
#include "ShapeObject.h"

class Actor;

class MeshComponent : public Component
{
	ShapeObject* shape;

public:
	FORCEINLINE ShapeObject* GetShape() const
	{
		return shape;
	}
	FORCEINLINE Vector2f GetSize() const
	{
		if (!shape || !shape->GetData().data.rectangleData)
			return { 0.f, 0.f }; // Valeur par défaut si erreur

		return shape->GetData().data.rectangleData->size;
	}

	FORCEINLINE float GetRadius() const
	{
		return shape->GetData().data.circleData->radius;
	}
	FORCEINLINE void SetShape(ShapeObject* _shape)
	{
		shape = _shape;
	}

public:
	MeshComponent(Actor* _owner, const float _radius, const size_t& _pointCount = 30, const string& _path = "", const IntRect& _rect = {});
	MeshComponent(Actor* _owner, const RectangleShapeData& _data);
	MeshComponent(Actor* _owner, const MeshComponent* _other);
	~MeshComponent();
};