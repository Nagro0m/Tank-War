#pragma once
#include "Object.h"
class TextObject : public Object
{
	Text* text;

public:
	FORCEINLINE virtual Drawable* GetDrawable() const override
	{
		return text;
	}

	#pragma region Setter
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
	FORCEINLINE virtual void SetRotation(const Angle& _angle)
	{
		Super::SetRotation(_angle);
		text->setRotation(_angle);
	}
	FORCEINLINE virtual void SetTransformData(const TransformData& _transformeData)
	{
		Super::SetTransformData(_transformeData);
		text->setOrigin(_transformeData.origin);
		text->setPosition(_transformeData.position);
		text->setScale(_transformeData.scale);
		text->setRotation(_transformeData.rotation);
	}
	#pragma endregion

	FORCEINLINE virtual void Move(const Vector2f& _offset)
	{
		Super::Move(_offset);
		text->move(_offset);
	}
	FORCEINLINE virtual void Scale(const Vector2f& _factor)
	{
		Super::Scale(_factor);
		text->scale(_factor);
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle)
	{
		Super::Rotate(_angle);
		text->rotate(_angle);
	}

public:
	TextObject();
	~TextObject();
};

