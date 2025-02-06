#pragma once
#include "Singleton.h"
#include "CollisionComponent.h"

class CollisionManager : public Singleton<CollisionManager>
{
	set<CollisionComponent*> allCollisionComponents;
	set<pair<Actor*, Actor*>> hasCollision;

public:
	FORCEINLINE void AddCollisionComponent(CollisionComponent* _component)
	{
		allCollisionComponents.insert(_component);
	}

	FORCEINLINE void RemoveColiisionComponents(CollisionComponent* _component)
	{
		allCollisionComponents.erase(_component);
	}

	FORCEINLINE set<CollisionComponent*> GetAllCollisionComponents() const
	{
		return allCollisionComponents;
	}

	FORCEINLINE bool ContainPair(Actor* _owner, Actor* _other)
	{
		if (hasCollision.contains({ _owner ,_other }) || hasCollision.contains({ _other ,_owner }))
		{
			return true;
		}
		return false;
	}

	FORCEINLINE void AddCollisionPair(Actor* _owner, Actor* _other)
	{
		if (!ContainPair(_owner, _other)) return;
		hasCollision.insert({ _owner , _other });
	}

	FORCEINLINE void ResetCollisionPair()
	{
		hasCollision.clear();
	}

	void Collide(const CollisionData& _owner, const CollisionData& _other);
};

