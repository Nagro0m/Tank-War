#pragma once
#include "Component.h"
#include "MeshActor.h"

enum InteractStatus
{
	IS_NONE,
	IS_QUERY,
	IS_PHYSIC,
	IS_ALL
};

enum CollisionType
{
	CT_NONE,
	CT_OVERLAP,
	CT_BLOCK
};

struct CollisionData
{
	Actor* other;
	CollisionType response;
	FloatRect impactRect;
};

class CollisionComponent : public Component
{
	string channelName;
	InteractStatus status;
	CollisionType type; // Réponse par défaut
	map<string, CollisionType> responses;

public:
	FORCEINLINE string GetChannelName() const
	{
		return channelName;
	}
 
public:
	CollisionComponent(Actor* _owner);
	CollisionComponent(Actor* _owner, const CollisionComponent& _other);

protected:
	virtual void Tick(const float _deltaTime) override;

private:
	void CheckCollision();
};
