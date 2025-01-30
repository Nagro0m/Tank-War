#include "Tank.h"
#include "InputManager.h"

namespace Tank
{
	Tank::Tank(const PlayerNumber& _playeNumber)
	{
		life = 100.0f;
		isMoving = true;
		allTankParts = map<TankPartType, shared_ptr<TankPart>>();
		movement = CreateComponent<MovementComponent>();
		collisions = CreateComponent<CollisionComponent>();
		playerNumber = _playeNumber;
	}

	void Tank::DetachPart(const TankPartType& _socketType)
	{
		if (!allTankParts.contains(_socketType)) return;
		RemoveChild(allTankParts.at(_socketType));
		allTankParts.at(_socketType).reset();
	}
	void Tank::Construct()
	{
		Super::Construct();
		const vector<function<void()>>& _bindTouchs =
		{
			[&]()
			{
				M_INPUT.BindAction(Code::Z, bind(&Tank::UpSpeed, this));
				M_INPUT.BindAction(Code::Q, bind(&Tank::TurnLeft, this));
				M_INPUT.BindAction(Code::D, bind(&Tank::TurnRight, this));
				M_INPUT.BindAction(Code::S, bind(&Tank::DownSpeed, this));
			},
			[&]()
			{
				M_INPUT.BindAction(Code::Up, bind(&Tank::UpSpeed, this));
				M_INPUT.BindAction(Code::Left, bind(&Tank::TurnLeft, this));
				M_INPUT.BindAction(Code::Right, bind(&Tank::TurnRight, this));
				M_INPUT.BindAction(Code::Down, bind(&Tank::DownSpeed, this));
			},
		};
		_bindTouchs[playerNumber]();
	}
	void Tank::UpSpeed()
	{
		movement->AddSpeed(1.0f); //TODO TWEAK VALUE AND TWEAK MAX IF CHANGE
	}
	void Tank::DownSpeed()
	{
		movement->AddSpeed(-1.0f); //TODO TWEAK VALUE AND TWEAK MAX IF CHANGE
	}
	void Tank::TurnLeft()
	{
		Rotate(degrees(5.0f));
		//TODO change direction for good movement
	}
	void Tank::TurnRight()
	{
		Rotate(degrees(-5.0f));
		//TODO change direction for good movement
	}
}