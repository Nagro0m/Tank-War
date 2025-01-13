#pragma once
#include "CoreMinimal.h"

struct TransformData
{
	Vector2f origin;
	Vector2f position;
	Vector2f scale;
	Angle rotation;
};
class Object
{
	TransformData transform;

public:
	FORCEINLINE virtual bool IsValid(Object* _object) const
	{
		return _object;
	}
	FORCEINLINE TransformData GetTransform() const
	{
		return transform;
	}
	FORCEINLINE Vector2f GetOrigin() const
	{
		return transform.origin;
	}	
	FORCEINLINE Vector2f GetScale() const
	{
		return transform.scale;
	}
	FORCEINLINE Vector2f GetPosition() const
	{
		return transform.position;
	}
	FORCEINLINE Angle GetRotation() const
	{
		return transform.rotation;
	}
	
	FORCEINLINE virtual Drawable* GetDrawable() const = 0;
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin)
	{
		transform.origin = _origin;
	}
	FORCEINLINE virtual void SetPosition(const Vector2f& _position)
	{
		transform.position = _position;
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale)
	{
		transform.scale = _scale;
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation)
	{
		transform.rotation = _rotation;
	}
	FORCEINLINE virtual void SetTransform(const TransformData& _transformData)
	{
		transform = _transformData;
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset)
	{
		transform.position += _offset;
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle)
	{
		transform.rotation += _angle;
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor)
	{
		transform.scale += _factor;
	}

public:
	virtual ~Object() {};

public:

	template<typename Type>
	Type* Cast(Object* _object)
	{
		if (!IsValid(_object)) return nullptr;
		return dynamic_cast<Type>(_object);
	}
};

