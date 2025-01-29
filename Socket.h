#pragma once
#include "Actor.h"

namespace Tank
{
	enum TankPart
	{
		Hull,
		Weapon,
		Track
	};

	class Socket : public Actor
	{
		TankPart type;

	public:
		FORCEINLINE TankPart GetTankPartType() const
		{
			return type;
		}

	public:
		Socket(const TankPart& _type);
		~Socket();
	};


}