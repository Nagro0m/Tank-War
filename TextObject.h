#pragma once
#include "Object.h"

class TextObject : public Object
{
	Text* text;

public:
	FORCEINLINE virtual Text* GetDrawable() const override
	{
		return text;
	}
	FORCEINLINE virtual void SetOrigin(const Vector2f& _origin)
	{
		Super::SetOrigin(_origin);
		text->setOrigin(_origin);
	}
	FORCEINLINE virtual void SetPosition(const Vector2f& _position)
	{
		Super::SetPosition(_position);
		text->setPosition(_position);
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale)
	{
		Super::SetScale(_scale);
		text->setScale(_scale);
	}
	FORCEINLINE virtual void SetRotation(const Angle& _rotation)
	{
		Super::SetRotation(_rotation);
		text->setRotation(_rotation);
	}
	FORCEINLINE virtual void SetTransform(const TransformData& _transformData)
	{
		Super::SetTransform(_transformData);
		text->setOrigin(_transformData.origin);
		text->setPosition(_transformData.position);
		text->setRotation(_transformData.rotation);
		text->setScale(_transformData.scale);
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset)
	{
		Super::Move(_offset);
		text->move(_offset);
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle)
	{
		Super::Rotate(_angle);
		text->rotate(_angle);
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor)
	{
		Super::Scale(_factor);
		text->setOrigin(_factor);
	}


	TextObject();
	~TextObject();
};