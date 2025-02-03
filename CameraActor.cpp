#include "CameraActor.h"
#include "GameManager.h"
#include "Game.h"


CameraActor::CameraActor(const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>();
	target = nullptr;
}

CameraActor::CameraActor(const Vector2f& _center, const Vector2f& _size, const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>(_center, _size);
	target = nullptr;
}

CameraActor::CameraActor(const FloatRect& _rect, const string& _name) : Actor(_name)
{
	camera = CreateComponent<CameraComponent>(_rect);
	target = nullptr;
}

CameraActor::CameraActor(const CameraActor& _other) : Actor(_other)
{
	camera = CreateComponent<CameraComponent>(_other.camera);
	target = nullptr; //TODO check
}

void CameraActor::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	SetPositionOnTarget();
}

void CameraActor::SetPositionOnTarget()
{
	//if (!target || !IsInTargetRect()) return;
	//SetPosition(target->GetPosition());


	if (!target) return;
	
	if (!IsInTargetRectX())
	{
		SetPosition(Vector2f( GetPosition().x, target->GetPosition().y));
		return;
	}

	if (!IsInTargetRectY())
	{
		SetPosition(Vector2f(target->GetPosition().x, GetPosition().y));
		return;
	}

	SetPosition(target->GetPosition());

}