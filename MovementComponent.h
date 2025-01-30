#pragma once
#include "Component.h"

class MovementComponent : public Component
{ 
	bool canMove;
	float speed;
	float maxSpeed;
	float mass;
	float gravity;
	Vector2f direction;

public:
	FORCEINLINE bool IsCanMove() const
	{
		return canMove;
	}
	FORCEINLINE void SetCanMove(const bool _canMove = true)
	{
		canMove = _canMove;
	}
	FORCEINLINE Vector2f& GetDirection()
	{
		return direction;
	}
	FORCEINLINE void SetSpeed(const float _speed)
	{
		if (_speed < -maxSpeed || _speed > maxSpeed) return;
		speed = _speed;
	}
	FORCEINLINE void AddSpeed(const float _speed)
	{
		if (_speed < -maxSpeed || _speed > maxSpeed) return;

		speed += _speed;
	}
public:
	MovementComponent(Actor* _owner);
	MovementComponent(Actor* _owner, const MovementComponent* _other);

protected:
	virtual void Tick(const float _deltaTime) override;

private:
	void Move(const float _deltaTime);
};