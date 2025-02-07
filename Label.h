#pragma once
#include "Widget.h"
#include "TextObject.h"

namespace UI
{
	class Label : public Widget
	{
		TextObject* text;

	public:
#pragma region Modifier
		FORCEINLINE void SetString(const string& _text)
		{
			text->GetDrawable()->setString(_text);
		}
		FORCEINLINE void SetColor(const Color& _color)
		{
			text->GetDrawable()->setFillColor(_color);
		}
		FORCEINLINE void SetCharacterSize(const u_int& _size)
		{
			text->GetDrawable()->setCharacterSize(_size);
		}

		FORCEINLINE void SetOriginAtMiddle()
		{
			FloatRect _bounds = text->GetDrawable()->getGlobalBounds();
			SetOrigin(_bounds.size / 2.0f);
		}
		FORCEINLINE virtual void SetPosition(const Vector2f& _position) override
		{
			Super::SetPosition(_position);
			text->SetPosition(_position);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _rotation) override
		{
			Super::SetRotation(_rotation);
			text->SetRotation(_rotation);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			text->SetScale(_scale);
		}
		FORCEINLINE virtual void SetOrigin(const Vector2f& _origin) override
		{
			Super::SetOrigin(_origin);
			text->SetOrigin(_origin);
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			text->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			text->Rotate(_angle);
		}
		FORCEINLINE virtual void Scale(const Vector2f& _factor) override
		{
			Super::Scale(_factor);
			text->Scale(_factor);
		}

#pragma endregion

	public:
		Label(const string& _text, const RenderType& _type = Screen, const string& _path = "", const FontExtensionType& _fontType = OTF);
		~Label();

	private:
		virtual void Render(RenderWindow& _window) override;
	};
}