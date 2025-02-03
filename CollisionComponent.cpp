#include "CollisionComponent.h"
#include "ActorManager.h"

CollisionComponent::CollisionComponent(Actor* _owner, const ActorType& _ownerType, const CollisionType& _type,
	const LayerType& _layer, const set<ActorType>& _blackList, const function<void()> _callback) 
	: Component(_owner)
{
	meshOwner = Cast<MeshActor>(_owner);
	ownerType = _ownerType;
	type = _type;
	layer = _layer;
	blackList = _blackList;
	callback = _callback;
}

CollisionComponent::CollisionComponent(Actor* _owner, const CollisionComponent* _other) : Component(_owner)
{
	meshOwner = _other->meshOwner;
	ownerType = _other->ownerType;
	type = _other->type;
	layer = _other->layer;
	blackList = _other->blackList;
	callback = _other->callback;
}

void CollisionComponent::Tick(const float _deltaTime)
{
	CheckCollision();
}

void CollisionComponent::CheckCollision()
{
	if (type == CT_NONE) return;

	const set<Actor*>& _allActors = M_ACTOR.GetAllActors();

	const FloatRect& _ownerRect = meshOwner->GetMesh()->GetShape()->GetDrawable()->getGlobalBounds();
	
	bool _isSkip = false;
	for (Actor* _actor : _allActors)
	{
		if (CollisionComponent* _actorCollisionComponent = _actor->GetComponent<CollisionComponent>())
		{
			if (_actorCollisionComponent->GetCollisionType() == CT_NONE 
			  || Contains(blackList, _actorCollisionComponent->GetActorType())) continue;

			const FloatRect& _actorRect = _actorCollisionComponent->meshOwner->GetMesh()->GetShape()->GetDrawable()->getGlobalBounds();
			if (const optional<FloatRect> _intersection = _ownerRect.findIntersection(_actorRect))
			{
				callback();
			}
		}
	}
}