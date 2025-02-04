#pragma once
#include "Component.h"
#include "MeshActor.h"

enum InteractStatus
{
	IS_NONE = 0,
	IS_QUERY = 1 << 0,
	IS_PHYSIC = 1 << 1,
	IS_ALL = IS_QUERY | IS_PHYSIC
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
	int status;
	CollisionType type; // Réponse par défaut
	map<string, CollisionType> responses; //Layer a la place du string

public:
	FORCEINLINE string GetChannelName() const
	{
		return channelName;
	}
 
public:
	CollisionComponent(Actor* _owner, string _channelName, int _status, CollisionType _type, map<string, CollisionType> _responses);
	CollisionComponent(Actor* _owner, const CollisionComponent& _other);

protected:
	virtual void Tick(const float _deltaTime) override;

private:
	void CheckCollision();
};
