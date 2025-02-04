#include "CollisionComponent.h"
#include "ActorManager.h"

CollisionComponent::CollisionComponent(Actor* _owner, string _channelName, int _status, CollisionType _type) : Component(_owner)
{
	channelName = _channelName;
	type = _type;
	status = _status;
}

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionComponent& _other) : Component(_owner)
{
	channelName = _other.channelName;
	type = _other.type;
	status = _other.status;
	responses = _other.responses;
}

void CollisionComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	CheckCollision();
}

void CollisionComponent::CheckCollision()
{
	// changer en flag et tester s'il contient le flag 'IS_PHYSIC'
	if (!(status & IS_PHYSIC)) return;

	const set<Actor*>& _allActors = M_ACTOR.GetAllActors();
	const FloatRect& _ownerRect = Cast<MeshActor>(owner)->GetHitbox();

	for (Actor* _other : _allActors)
	{
		if (_other == owner) continue;

		if (CollisionComponent* _otherCollision = _other->GetComponent<CollisionComponent>())
		{
			const string& _otherName = _otherCollision->GetChannelName();
			if (!responses.contains(_otherName)) continue;

			const CollisionType& _response = responses.at(_otherName);
			if (_response == CT_NONE) continue;

			const FloatRect& _otherRect = Cast<MeshActor>(_other)->GetHitbox();
			if (const optional<FloatRect> _intersection = _ownerRect.findIntersection(_otherRect))
			{
				const CollisionData& _data = { _other, _response, *_intersection };

				if (currentCollisions.contains(_other))
				{
					owner->OnCollisionUpdate(_data);
				}
				else
				{
					owner->OnCollisionEnter(_data);

					currentCollisions.insert(_other);
				}

				/*owner->OnCollision(_data);
				_other->OnCollision(_data);*/
			}
			else
			{
				if (currentCollisions.contains(_other))
				{
					owner->OnCollisionExit(_other);
					currentCollisions.erase(_other);
				}
			}
		}
	}
}