#include "Hull.h"
#include "Weapon.h"
#include "Actor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

namespace Tank
{
	
	class Tank : public Actor
	{
		////Corps du tank
		//Hull* hull;
		////Canon
		//Weapon* weapon;
		////Chenilles
		//Track* track;
		map<TankPartType, shared_ptr<TankPart>> allTankParts;
		int life;
		bool isMoving;
		MovementComponent* movement;
		CollisionComponent* collisions;
	public:


	public:
		Tank();

	public:
		template<typename Type, IS_BASE_OF(TankPart, Type)>
		void AttachPart(const TankPartType& _socketType, shared_ptr<Type> _part)
		{
			if (!_part || allTankParts.at(_socketType))
			{
				LOG(Error, "Erreur : tentative d'attacher un pointeur nul" + to_string(_socketType));
				return;
			}
			AddChild(_part, AT_SNAP_TO_TARGET);
			allTankParts[_socketType] = _part;
		}
		void Detachpart(const TankPartType& _socketType);
	};
}