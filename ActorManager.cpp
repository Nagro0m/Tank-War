#include "ActorManager.h"

void ActorManager::BeginPlay()
{
	for (Actor* _actor : allActors)
	{
		_actor->BeginPlay();
	}
}

void ActorManager::Tick(const float _deltaTime)
{
}

void ActorManager::BeginDestroy()
{
}
