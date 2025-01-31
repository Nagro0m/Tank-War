#include "Hull.h"
#include "Weapon.h"
#include "Actor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

namespace Tank
{
	enum PlayerNumber
	{
		Player_1,
		Player_2,
	};
	class TankActor : public Actor
	{
		////Corps du tank
		//Hull* hull;
		////Canon
		//Weapon* weapon;
		////Chenilles
		//Track* track;
		PlayerNumber playerNumber;
		map<TankPartType, shared_ptr<TankPart>> allTankParts;
		int life;
		bool isMoving;
		MovementComponent* movement;
		CollisionComponent* collisions;

	public:
		TankActor(const PlayerNumber& _playeNumber = Player_1);

	public:
		template<typename Type, IS_BASE_OF(TankPart, Type)>
		void AttachPart(const TankPartType& _socketType, shared_ptr<Type> _part)
		{
			if (!_part)
			{
				LOG(Error, "Erreur : tentative d'attacher un pointeur nul" + to_string(_socketType));
				return;
			}
			AddChild(_part, AT_SNAP_TO_TARGET);
			allTankParts[_socketType] = _part;
		}
		void DetachPart(const TankPartType& _socketType);

		virtual void Construct() override;
	private:
		void UpSpeed();
		void DownSpeed();
		void TurnLeft();
		void TurnRight();
	};
}