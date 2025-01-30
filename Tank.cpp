#include "Tank.h"
#include "InputManager.h"

namespace Tank
{
	TankActor::TankActor(const PlayerNumber& _playeNumber)
	{
		life = 100.0f;
		isMoving = true;
		allTankParts = map<TankPartType, shared_ptr<TankPart>>();
		movement = CreateComponent<MovementComponent>();
		collisions = CreateComponent<CollisionComponent>();
		playerNumber = _playeNumber;
	}

	void TankActor::DetachPart(const TankPartType& _socketType)
	{
		if (!allTankParts.contains(_socketType)) return;
		RemoveChild(allTankParts.at(_socketType));
		allTankParts.at(_socketType).reset();
	}
	void TankActor::Construct()
	{
		Super::Construct();
		const vector<function<void()>>& _bindTouchs =
		{
			[&]()
			{
				M_INPUT.BindAction(Code::Z, bind(&TankActor::UpSpeed, this), "Player1_Up", false);
				M_INPUT.BindAction(Code::Q, bind(&TankActor::TurnLeft, this), "Player1_Left", false);
				M_INPUT.BindAction(Code::D, bind(&TankActor::TurnRight, this), "Player1_Right", false);
				M_INPUT.BindAction(Code::S, bind(&TankActor::DownSpeed, this), "Player1_Down", false);
			},
			[&]()
			{
				M_INPUT.BindAction(Code::Up, bind(&TankActor::UpSpeed, this), "Player1_Up", false);
				M_INPUT.BindAction(Code::Left, bind(&TankActor::TurnLeft, this), "Player1_Left", false);
				M_INPUT.BindAction(Code::Right, bind(&TankActor::TurnRight, this), "Player1_Right", false);
				M_INPUT.BindAction(Code::Down, bind(&TankActor::DownSpeed, this), "Player1_Down", false);
			},
		};
		_bindTouchs[playerNumber]();

		//TODO activer les InputData au lancement du jeu après la création
	}
	void TankActor::UpSpeed()
	{
		movement->AddSpeed(1.0f); //TODO TWEAK VALUE AND TWEAK MAX IF CHANGE
	}
	void TankActor::DownSpeed()
	{
		movement->AddSpeed(-1.0f); //TODO TWEAK VALUE AND TWEAK MAX IF CHANGE
	}
	void TankActor::TurnLeft()
	{
		Rotate(degrees(5.0f));
		//TODO change direction for good movement
	}
	void TankActor::TurnRight()
	{
		Rotate(degrees(-5.0f));
		//TODO change direction for good movement
	}
}