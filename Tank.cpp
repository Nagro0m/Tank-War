#include "Tank.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "MeshActor.h"

Tank::Tank(vector<Code> _code, const string& _path, float _fuelTank) : MeshActor(RectangleShapeData(Vector2f(60.0f, 110.0f), _path))
{
	life = 100.0f;
	fuelTank = _fuelTank;
	isMoving = false;
	movement = CreateComponent<MovementComponent>(1.0f);
	collision = CreateComponent<CollisionComponent>("Tank", IS_ALL, CT_OVERLAP);
	pitch = 1.0f;
	sound = nullptr;
	rearSound = nullptr;
	maxSpeed = 10.0f;
	code = _code;
	SetLayer(Layer::LayerType::PLAYER);

	vector<pair<string, CollisionType>> _responsesTank = {{"BardedWire", CT_BLOCK}, {"Root", CT_BLOCK}, {"Grass", CT_BLOCK} , {"Tree", CT_BLOCK} ,{"Rock", CT_BLOCK} };
	collision->AddResponses(_responsesTank);
}

Tank::Tank(const Tank& _other) : MeshActor(_other)
{
	life = _other.life;
	fuelTank = _other.fuelTank;
	isMoving = _other.isMoving;
	movement = CreateComponent<MovementComponent>(_other.movement);
	collision = CreateComponent<CollisionComponent>(*_other.collision);
	pitch = _other.pitch;
	sound = _other.sound;
	rearSound = _other.rearSound;
	maxSpeed = _other.maxSpeed;
	code = _other.code;
	distance = 0.0f;
}

void Tank::Construct()
{
	Super::Construct();

	SetOriginAtMiddle();
	PlaySample();
	SoundSample* _backgroundEngineSound = M_AUDIO.PlaySample<SoundSample>("Tank_Engine");
	_backgroundEngineSound->SetLoop(true);
	_backgroundEngineSound->SetVolume(5.0f);

	M_INPUT.BindAction({ code[0]}, bind(&Tank::Left, this));
	M_INPUT.BindAction({ code[1] }, bind(&Tank::Right, this));
	M_INPUT.BindAction({ code[2] }, bind(&Tank::SpeedUp, this));
	M_INPUT.BindAction({ code[3] }, bind(&Tank::SlowDown, this));

	ComputeDirection(0.0f);
}

void Tank::BeginPlay()
{
	Super::BeginPlay();

}

void Tank::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	movement->SetIsMoving(isMoving);
	
	if (fuelTank != -1.0f)
	{
		UpdateFuelTank(_deltaTime);
	}
}

void Tank::CollisionEnter(const CollisionData& _data)
{
	if (IsToDelete()) return;
	if (_data.response == CT_BLOCK)
	{
		if (_data.other->GetLayer() == Layer::LayerType::BREAKABLE)
		{
			if (HasMaxSpeed())
			{
				_data.other->SetToDelete();
			}
		}
	}

	else if (_data.response == CT_OVERLAP)
	{
		if (_data.other->GetLayer() == Layer::LayerType::RETRIEVABLE)
		{

		}
	}
	
	distance += (1 ) * movement->GetSpeed();
	SpawnEffect();
}

void Tank::CollisionUpdate(const CollisionData& _data)
{
	if (IsToDelete()) return;
}

void Tank::CollisionExit(const CollisionData& _data)
{
	if (IsToDelete()) return;
}

void Tank::ComputeDirection(const float _rotation)
{
	Rotate(degrees(_rotation));
	float _radians = (GetRotation().asDegrees() - 90.0f) * pi / 180.0f;
	Vector2f _direction = Vector2f(cos(_radians), sin(_radians));
	movement->SetDirection(_direction);
}

void Tank::Right()
{
	ComputeDirection(2);
}

void Tank::Left()
{
	ComputeDirection(-2);
}

void Tank::SpeedUp()
{
	isMoving = true;
	float _speed = movement->GetSpeed();

	//if (speed >= maxSpeed) return;
	if (rearSound)
	{
		rearSound->Stop();
		rearSound = nullptr;
	}

	movement->SetSpeed(_speed + 10.0f);

	if (sound)
	{
		M_AUDIO.PlaySample<SoundSample>("Gear_Shift");
		if (pitch <= 1.9f)
		{
			pitch += 0.1f;
		}
		sound->SetPitch(pitch);
	}
}

void Tank::SlowDown()
{
	float _speed = movement->GetSpeed();

	if (_speed <= -10.0f)
	{
		_speed = -10.0f;
	}
	else
	{
		_speed -= 10.0f;
	}

	movement->SetSpeed(_speed);
	isMoving = (_speed != 0);

	if (_speed < 0)
	{
		if (!rearSound)
		{
			rearSound = M_AUDIO.PlaySample<SoundSample>("RearSound");
		}
	}
	else if (rearSound)
	{
		rearSound->Stop();
		rearSound = nullptr;
	}

	if (sound)
	{
		M_AUDIO.PlaySample<SoundSample>("Gear_Shift");
		if (pitch >= 0.8f)
		{
			pitch -= 0.1f;
		}
		sound->SetPitch(pitch);
	}
}

void Tank::PlaySample()
{
	sound = M_AUDIO.PlaySample<SoundSample>("Tank_Engine", WAV);
	sound->SetVolume(35.0f);
	sound->SetLoop(true);
}

void Tank::Life()
{

}

void Tank::UpdateFuelTank(const float _deltaTime)
{
	const float _speed = movement->GetSpeed();
	fuelTank = _speed > 0 ? fuelTank - (maxSpeed - _speed + 1)* _deltaTime : fuelTank - 1 * _deltaTime;
	fuelTank = fuelTank <= 0 ? 0 : fuelTank;
	if (fuelTank == 0) isMoving = false;
	LOG(Display, to_string(fuelTank));
}

void Tank::Refuel()
{
	fuelTank = fuelTank + 50 > 100 ? 100 : fuelTank + 50;
	LOG(Display, to_string(fuelTank));
}
void Tank::SpawnEffect()
{
	if (distance >= 50 )
	{
		MeshActor* _effect = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(20, 20), "Effects/Tire_Track_02"), "shit", 3.0f));
		_effect->SetPosition(GetPosition());
		_effect->Rotate(GetRotation());
		distance = 0;
	}
	
}


