#include "FuelGameplay.h"
#include "CollisionComponent.h"
#include "Level.h"
#include "CameraManager.h"
#include "Tank.h"
#include "MeshTest.h"
#include "InputManager.h"
using namespace Input;

FuelGameplay::FuelGameplay()
{
	player1Tank = nullptr;
}

FuelGameplay::~FuelGameplay()
{
}

void FuelGameplay::Start()
{
	Super::Start();

	vector<Key> _tank1 =
	{
		Key::A,
		Key::D,
		Key::W,
		Key::S,
	};

	player1Tank = Level::SpawnActor(Tank(_tank1, "Tank/Tank_1", "Player1"));
	player1Tank->SetPosition({ 600.0f, 600.0f });

	vector<pair<string, CollisionType>> _responsesTank ={{"Rock", CT_BLOCK}};
	player1Tank->GetCollision()->AddResponses(_responsesTank);


	MeshTest* _meshTest = Level::SpawnActor<MeshTest>(MeshTest(RectangleShapeData({100.0f,100.0f}, "Object/Rock_4")));
	_meshTest->SetPosition(Vector2f(400.0f, 400.0f));
	vector<pair<string, CollisionType>> _responsesMesh = { { "Tank", CT_OVERLAP } };
	_meshTest->GetCollision()->AddResponses(_responsesMesh);
	

	Vector2f _windowSize = Vector2f(window.getSize());
	//_meshActor->SetPosition(Vector2f( window.getSize().x / 2, window.getSize().y / 2 ));

	CameraActor* cameraPlayer1 = Camera::M_CAMERA.CreateCamera(CameraActor(_windowSize / 2.0f, Vector2f(1920, 1080), "MeshActorCamera1"));
	cameraPlayer1->SetViewport(window.getDefaultView().getViewport());
	//cameraPlayer1->SetTarget(_meshActor);


}

bool FuelGameplay::Update()
{
	Super::Update();



	return IsOver();
}

void FuelGameplay::Stop()
{
	Super::Stop();
}
