#include "FuelGameplay.h"
#include "Level.h"
#include "CameraManager.h"
#include "Tank.h"
#include "CollisionComponent.h";
#include "MeshTest.h"

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

	vector<Code> _tank1 =
	{
		Code::A,
		Code::D,
		Code::W,
		Code::S,
	};

	player1Tank = Level::SpawnActor(Tank(_tank1, "Tank/Tank_1", 100.0f));
	player1Tank->SetPosition({ 600.0f, 600.0f });

	MeshTest* _meshTest = Level::SpawnActor<MeshTest>(MeshTest(RectangleShapeData({100.0f,100.0f}, "Object/Rock_4")));
	_meshTest->SetPosition(Vector2f(400.0f, 400.0f));
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
