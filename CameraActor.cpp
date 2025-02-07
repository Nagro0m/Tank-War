#include "CameraActor.h"
#include "GameManager.h"
#include "Game.h"


CameraActor::CameraActor(const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>();
	target = nullptr;
	isOnTargetRect = false;
}

CameraActor::CameraActor(const Vector2f& _center, const Vector2f& _size, const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>(_center, _size);
	target = nullptr;
	isOnTargetRect = false;
}

CameraActor::CameraActor(const FloatRect& _rect, const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>(_rect);
	target = nullptr;
	isOnTargetRect = false;
}

CameraActor::CameraActor(const CameraActor& _other) : Actor(_other)
{
	camera = CreateComponent<CameraComponent>(_other.camera);
	target = nullptr; //TODO check
	isOnTargetRect = false;
}

void CameraActor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	SetPositionOnTarget();
}

void CameraActor::SetPositionOnTarget()
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