#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "Bullet.h"

class Tank : public MeshActor
{
	int life;
	float fuelTank;
	bool isMoving;
	MovementComponent* movement;
	CollisionComponent* collision;
	float pitch;
	SoundSample* sound;
	SoundSample* rearSound;
	float maxSpeed;
	vector<Code> code;
	float distance;

public:
	FORCEINLINE int GetLife() const 
	{
		return life;
	}

	FORCEINLINE void ResetSpeed()
	{
		movement->SetSpeed(0.0f);
	}
	
	FORCEINLINE CollisionComponent* GetCollision() const
	{
		return collision;
	}


	FORCEINLINE bool HasMaxSpeed() const
	{
		return movement->GetSpeed() == maxSpeed;
	}
	FORCEINLINE void SetMaxSpeed(float _value) 
	{
		maxSpeed = _value;
	}
	FORCEINLINE float GetSpeed() const
	{
		return movement->GetSpeed();
	}

public:
	Tank(vector<Code> _code, const string& _path, float _fuelTank = -1.0f);

	Tank(const Tank& _other);

	void Construct();

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;


	void ComputeDirection(const float _rotation);
	void Right();
	void Left();
	void SpeedUp();
	void SlowDown();
	void Shoot();
	void PlaySample();
	void Life();
	void UpdateFuelTank(const float _deltaTime);
	void Refuel();
	void SpawnEffect();
};
