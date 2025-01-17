#pragma once
#include "CoreMinimal.h"

struct TransformData
{
	Vector2f origin;
	Vector2f position;
	Angle rotation;
	Vector2f scale;
};

class Object
{
protected:
	TransformData transform;

public:
	FORCEINLINE virtual bool IsValid(Object* _object) const
	{
		return _object;
	}
	#pragma region Getter
	FORCEINLINE virtual TransformData GetTransform() const
	{
		return transform;
	}
	FORCEINLINE  Vector2f GetOrigin() const
	{
		return transform.origin;
	}
	FORCEINLINE  Vector2f GetPosition() const
	{
		return transform.position;
	}
	FORCEINLINE  Vector2f GetScale() const
	{
		return transform.scale;
	}
	FORCEINLINE  Angle GetRotation() const
	{
		return transform.rotation;
	}
	FORCEINLINE virtual Drawable* GetDrawable() const = 0;
    #pragma endregion

	#pragma region Setter
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
	FORCEINLINE virtual void SetRotation(const Angle& _angle)
	{
		transform.rotation = _angle;
	}
	FORCEINLINE virtual void SetTransformData(const TransformData& _transformeData)
	{
		transform = _transformeData;
	}
	#pragma endregion

	FORCEINLINE virtual void Move(const Vector2f& _offset)
	{
		transform.position += _offset;
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor)
	{
		transform.scale += _factor;
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle)
	{
		transform.rotation += _angle;
	}

public:
	virtual ~Object() {};

public:
	template <typename T>
	T* Cast(Object* _object)
	{
		if (!IsValid(_object)) return nullptr;
		return dynamic_cast<T>(_object);
	}
};

