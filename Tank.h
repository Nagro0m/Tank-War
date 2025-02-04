#include "MeshActor.h"
#include "MovementComponent.h"
#include "CollisionComponent.h"
#include "AudioManager.h"
#include "InputManager.h"

class Tank : public MeshActor
{
	int life;
	float fuelTank;
	bool isMoving;
	MovementComponent* movement;
	CollisionComponent* collisions;
	Vector2f move;
	float speed;
	float pitch;
	SoundSample* sound;
	SoundSample* rearSound;
	float maxSpeed;
	vector<Code> code;
public:


public:
	Tank(vector<Code> _code, const string& _path, float _fuelTank = -1.0f);

	Tank(const Tank& _other);

	void Construct();

public:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void OnCollision(const CollisionData& _data) override;


	void ComputeDirection(const float _rotation);
	void Right();
	void Left();
	void SpeedUp();
	void SlowDown();
	void PlaySample();
	void Life();
	void UpdateFuelTank(const float _deltaTime);
	void Refuel();
};
