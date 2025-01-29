#pragma once
#include "Actor.h"

namespace Tank
{
	enum TankPart
	{
		Hull,
		Weapon,
		Track_Left,
		Track_Right,
	};

	class Socket : public Actor
	{

	public:
		TankPart partType;

	public:
		FORCEINLINE TankPart GetTankPartType() const
		{
			return partType;
		}

	public:
		Socket(const TankPart& _type);
		~Socket();
	};
}s
