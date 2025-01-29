#pragma once
#include "Hull.h"
#include "Weapon.h"
#include "Track.h"
#include "Socket.h"


namespace Tank
{
<<<<<<< Updated upstream
	enum TankPart
	{
		Hull,
		Weapon,
		Track
	};
=======
	
>>>>>>> Stashed changes

	class Tank : public MeshActor
	{
		////Corps du tank
		//Hull* hull;
		////Canon
		//Weapon* weapon;
		////Chenilles
		//Track* track;

		int life;
		bool isMoving;

	public:
		Actor* GetPart(const TankPart& _socketName) const
		{

		}

	public:
<<<<<<< Updated upstream
		Tank();
		~Tank();

	public:
		void Attachpart(const TankPart& _socketName, Actor* _part);
		void Detachpart(const TankPart& _socketName);
=======
		Tank(const Vector2f& _size);
		~Tank();

	public:
		void InitSocket();
		void AttachPart(const TankPart& _socketName, Actor* _part);
		void DetachPart(const TankPart& _socketName);
>>>>>>> Stashed changes
	};
}

