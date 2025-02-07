#pragma once
#include "CameraActor.h"

class FollowCamera : public CameraActor
{
	Actor* target;
	bool isOnTargetRect;
	FloatRect targetRect;

public:
	FORCEINLINE void SetViewport(const FloatRect& _rect)
	{
		Super::SetViewport(_rect);
	}
	FORCEINLINE virtual void SetPosition(const Vector2f& _center) override
	{
		Super::SetPosition(_center);
	}
	FORCEINLINE virtual void SetRotation(const Angle& _angle) override
	{
		Super::SetRotation(_angle);
	}
	FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
	{
		Super::SetScale(_scale);
	}
	FORCEINLINE virtual void Move(const Vector2f& _offset) override
	{
		Super::Move(_offset);
	}
	FORCEINLINE virtual void Rotate(const Angle& _angle) override
	{
		Super::Rotate(_angle);
	}
	FORCEINLINE void SetTarget(Actor* _target)
	{
		target = _target;
	}
	FORCEINLINE void SetTargetRect(FloatRect _targetRect)
	{
		isOnTargetRect = true;
		targetRect = _targetRect;
	}
	FORCEINLINE bool HasTarget() const
	{
		return target;
	}

public:
	FollowCamera(const string& _name);
	FollowCamera(const Vector2f& _center, const Vector2f& _size, const string& _name);
	FollowCamera(const Vector2f& _size, const string& _name);
	FollowCamera(const FloatRect& _rect, const string& _name);
	FollowCamera(const FollowCamera& _other);

private:

	FORCEINLINE bool IsInTargetRectX() const
	{
		return	target->GetPosition().x >= targetRect.position.x &&
			target->GetPosition().x <= targetRect.size.x;
	}
	FORCEINLINE bool IsInTargetRectY() const
	{
		return	target->GetPosition().y >= targetRect.position.y &&
			target->GetPosition().y <= targetRect.size.y;
	}

	virtual void Tick(const float _deltaTime) override;

	void SetPositionOnTarget();


};

