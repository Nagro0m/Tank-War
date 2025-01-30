#pragma once
#include "TankPart.h"
#include "AnimationComponent.h"

namespace Tank
{
	class Track : public TankPart
	{
		//Pas utile pour le moment, mais peut permettre d'ajouter des features de vitesses etc.
		//int weight;
		//Feature pour ajouter une protection supplémentaire
		//int protectionBonus;

		//Les traces laissé derriere la chenille
		MeshActor* trackMark;
		Animation* animation;

	public:
		Track();

	public:
		void Move(const Vector2f _newPosition);
	};
}