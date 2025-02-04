#include "Tank.h"
#include "CameraManager.h"
#include "TimerManager.h"

Tank::Tank(vector<Code> _code, const string& _path, float _fuelTank) : MeshActor(RectangleShapeData(Vector2f(60.0f, 110.0f), _path))
{
	life = 100.0f;
	fuelTank = _fuelTank;
	isMoving = true;
	movement = CreateComponent<MovementComponent>();
	collisions = CreateComponent<CollisionComponent>("Tank", IS_ALL, CT_OVERLAP, map<string, CollisionType>{{"Rock", CT_BLOCK}});
	speed = 1.0f;
	pitch = 1.0f;
	sound = nullptr;
	rearSound = nullptr;
	maxSpeed = 10.0f;
	code = _code;

	SetLayer(Layer::LayerType::PLAYER);
}

Tank::Tank(const Tank& _other) : MeshActor(_other)
{
	life = _other.life;
	fuelTank = _other.fuelTank;
	isMoving = _other.isMoving;
	movement = CreateComponent<MovementComponent>(_other.movement);
	collisions = CreateComponent<CollisionComponent>(*_other.collisions);
	speed = _other.speed;
	pitch = _other.pitch;
	sound = _other.sound;
	rearSound = _other.rearSound;
	maxSpeed = _other.maxSpeed;
	code = _other.code;
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

	if (isMoving)
	{
		Move(move * speed * _deltaTime * 10.0f);
	}
	if (fuelTank != -1.0f)
	{
		UpdateFuelTank(_deltaTime);
	}
}

void Tank::OnCollision(const CollisionData& _data)
{
	if (_data.response == CT_BLOCK)
	{
		if (_data.other->GetLayer() == Layer::LayerType::BREAKABLE)
		{
			if (HasMaxSpeed())
			{
				_data.other->SetToDelete();
				//LOG(Display, "crossed");
			}
		}
		
	}
	//if(_data.response == CT_OVERLAP)
}

void Tank::ComputeDirection(const float _rotation)
{
	Rotate(degrees(_rotation));
	float _radians = (GetRotation().asDegrees() - 90.0f) * pi / 180.0f; // Convertir en radians
	Vector2f _direction = Vector2f(cos(_radians), sin(_radians));

	move = _direction;
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
	if (speed >= 10) return;
	if (rearSound)
	{
		rearSound->Stop();
	}
	speed += 1;
	if (sound)
	{
		M_AUDIO.PlaySample<SoundSample>("Gear_Shift");
		if (pitch <= 1.9f)
		{
			pitch += 0.1f;
			cout << pitch << endl;
		}

		sound->SetPitch(pitch);
	}
}

void Tank::SlowDown()
{
	if (speed <= -1)
	{
		speed = -1;
		return;
	}

	if (speed <= 0)
	{
		rearSound = M_AUDIO.PlaySample<SoundSample>("RearSound");
	}
		
		
	speed -= 1;
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
	fuelTank = speed > 0 ? fuelTank - (maxSpeed - speed + 1)* _deltaTime : fuelTank - 1 * _deltaTime;
	fuelTank = fuelTank <= 0 ? 0 : fuelTank;
	if (fuelTank == 0) isMoving = false;
	LOG(Display, to_string(fuelTank));
}

void Tank::Refuel()
{
	fuelTank = fuelTank + 50 > 100 ? 100 : fuelTank + 50;
	LOG(Display, to_string(fuelTank));
}

