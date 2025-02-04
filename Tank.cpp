#include "Tank.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "MeshActor.h"

Tank::Tank(vector<Code> _code, const string& _path) : MeshActor(RectangleShapeData(Vector2f(60.0f, 110.0f), _path))
{
	life = 100.0f;
	isMoving = false;
	movement = CreateComponent<MovementComponent>();
	speed = 1.0f;
	pitch = 1.0f;
	sound = nullptr;
	rearSound = nullptr;
	maxSpeed = 10.0f;
	code = _code;
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



	new Timer(bind(&Tank::SpawnEffect, this), seconds(0.5), true, true);

	ComputeDirection(0.0f);
}

void Tank::BeginPlay()
{
	Super::BeginPlay();

}

void Tank::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	Move(move * speed * _deltaTime * 10.0f);
	LOG(Display, to_string(speed));
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

void Tank::SpawnEffect()
{
	MeshActor* _effect = Level::SpawnActor(MeshActor(RectangleShapeData(Vector2f(20, 20), "Effects/Tire_Track_02")));
	_effect->SetPosition(GetPosition());
	_effect->Rotate(GetRotation());
	
}



