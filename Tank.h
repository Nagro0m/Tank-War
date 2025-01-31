#include "MeshActor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"

class Tank : public MeshActor
{
	int life;
	bool isMoving;
	MovementComponent* movement;
	//CollisionComponent* collisions;
	Vector2f move;
	float speed;
public:


public:
	Tank(const string& _path);

	void Construct();

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

	void ComputeDirection(const float _rotation);
	void Right();
	void Left();
	void SpeedUp();
	void SlowDown();
};
