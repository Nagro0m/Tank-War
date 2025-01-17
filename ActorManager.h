#pragma once
#include "Singleton.h"
#include "Actor.h"
class ActorManager : public Singleton<ActorManager>
{
	set<Actor*> allActors;

public:
	FORCEINLINE set<Actor*> GetAllActors() const
	{
		return allActors;
	}

	FORCEINLINE void AddActor(Actor* _actor)
	{
		allActors.insert(_actor);
	}

public:
	~ActorManager();

public:
	virtual void BeginPlay() ;
	virtual void Tick(const float _deltaTime) ;
	virtual void BeginDestroy() ;
};

