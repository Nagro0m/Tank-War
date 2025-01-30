#pragma once
#include "MeshActor.h"

namespace Tank
{
	enum TankPartType
	{
		Hull_Part,
		Weapon_Part,
		Tracks_Part,
	};

	class TankPart : public MeshActor
	{
		TankPartType partType;

	public:
		FORCEINLINE TankPartType GetTankPartType() const
		{
			return partType;
		}

	public:
		TankPart(const TankPartType& _type, const RectangleShapeData& _rectangleShapeData);
	};
}