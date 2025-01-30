#include "Tank.h"


namespace Tank
{
	Tank::Tank()
	{
		life = 100.0f;
		isMoving = true;
		allTankParts = map<TankPartType, shared_ptr<TankPart>>();
	}


	void Tank::Detachpart(const TankPartType& _socketType)
	{
		if (!allTankParts.contains(_socketType)) return;
		RemoveChild(allTankParts.at(_socketType));
		allTankParts.at(_socketType).reset();
	}
}