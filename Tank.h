#pragma once
#include "MeshActor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "AudioManager.h"
#include "Bullet.h"
#include "AnimationComponent.h"
#include "InputManager.h"
using namespace Input;

class Tank : public MeshActor
{
	int life;
	float fuelTank;
	bool isMoving;
	MovementComponent* movement;
	//AnimationComponent* animation;
	float pitch;
	SoundSample* sound;
	SoundSample* rearSound;
	float maxSpeed;
	bool isReadyToShoot;
	vector<KeyType> code;
	float distance;
	string name;

	FORCEINLINE void SetIsReadyToShoot()
	{
		isReadyToShoot = true;
	}
public:
	FORCEINLINE int GetLife() const 
	{
		return life;
	}
	FORCEINLINE void ResetSpeed()
	{
		movement->SetSpeed(0.0f); // D'abord, on arrête le mouvement

		// Normalisation manuelle de la direction
		Vector2f _direction = movement->GetDirection();
		float _length = sqrt(_direction.x * _direction.x + _direction.y * _direction.y);

		if (_length > 0.0f) // Éviter la division par zéro
		{
			_direction.x /= _length;
			_direction.y /= _length;
		}

		SetPosition(GetPosition() - _direction * 1.0f); // Corrige la position
		pitch = 1.0f;
		sound->SetPitch(pitch);
	}


	FORCEINLINE void AddDamage(const int _dammage)
	{
		life -= _dammage;
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
	Tank(vector<KeyType> _code, const string& _path, const string& _name, float _fuelTank = -1.0f);

	Tank(const Tank& _other);

	void Construct();
	void Deconstruct();

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
	void ChangeLife( float _offset);
	void UpdateFuelTank(const float _deltaTime);
	void Refuel();
	void SpawnTireTrack();
	void Die();
};
