#include "FollowCamera.h"

FollowCamera::FollowCamera(const string& _name) : CameraActor(_name)
{
	target = nullptr;
	isOnTargetRect = false;
}

FollowCamera::FollowCamera(const Vector2f& _center, const Vector2f& _size, const string& _name) : CameraActor(_center, _size, _name)
{
	target = nullptr;
	isOnTargetRect = false;
}

FollowCamera::FollowCamera(const Vector2f& _size, const string& _name) : CameraActor(_size, _name)
{
	target = nullptr;
	isOnTargetRect = false;
}

FollowCamera::FollowCamera(const FloatRect& _rect, const string& _name) : CameraActor(_rect, _name)
{
	target = nullptr;
	isOnTargetRect = false;
}

FollowCamera::FollowCamera(const FollowCamera& _other) : CameraActor(_other)
{
	target = _other.target; 
	isOnTargetRect = _other.isOnTargetRect;
	targetRect = _other.targetRect;
}

void FollowCamera::Tick(const float _deltaTime)
{
	CameraActor::Tick(_deltaTime);

	SetPositionOnTarget();
}

void FollowCamera::SetPositionOnTarget()
{
	if (!target) return;
	

	Vector2f _newPosition = GetPosition();

	if (isOnTargetRect)
	{
		if (IsInTargetRectX())
		{
			_newPosition.x = target->GetPosition().x;
		}

		if (IsInTargetRectY())
		{
			_newPosition.y = target->GetPosition().y;
		}
	}

	SetPosition(_newPosition);
}
