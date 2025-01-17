#include "Component.h"
#include "Actor.h"

Component::Component(Actor* _actor)
{
	owner = _actor;
}

void Component::BeginPlay()
{
}

void Component::Tick(const float _deltaTime)
{
}

void Component::BeginDestroy()
{
}
