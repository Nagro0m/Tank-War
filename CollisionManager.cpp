#include "CollisionManager.h"

void CollisionManager::Collide(const CollisionData& _owner, const CollisionData& _other)
{
	if (_other.step == CS_ENTER)
	{
		_owner.other->CollisionEnter(_other);
		_other.other->CollisionEnter(_owner);
	}
	else if (_other.step == CS_UPDATE)
	{
		_owner.other->CollisionUpdate(_other);
		_other.other->CollisionUpdate(_owner);
	}
	else if (_other.step == CS_EXIT)
	{
		_owner.other->CollisionExit(_other);
		_other.other->CollisionExit(_owner);
	}
	AddCollisionPair(_owner.other, _other.other);
}
