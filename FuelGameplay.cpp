#include "FuelGameplay.h"
#include "CollisionComponent.h"
#include "Level.h"
#include "CameraManager.h"
#include "Tank.h"
#include "MeshTest.h"
#include "InputManager.h"
using namespace Input;
#include "Rock.h"
#include "Tree.h"

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

	vector<KeyType> _tank1 =
	{
		KeyType::A,
		KeyType::D,
		KeyType::W,
		KeyType::S,
	};

	player1Tank = Level::SpawnActor(Tank(_tank1, "Tank/Tank_1", "Player1"));
	player1Tank->SetPosition({ 600.0f, 600.0f });
	
	//Rock* _rock = new Rock(RectangleShapeData({ 100.0f,100.0f }, "Object/Rock_4"));
	Rock* _meshactor = Level::SpawnActor<Rock>(Rock(RectangleShapeData({ 100.0f,100.0f }, "Object/Rock_4")));
	_meshactor->SetPosition(Vector2f(400.0f, 400.0f));

	Tree* _meshactor2 = Level::SpawnActor<Tree>(Tree(RectangleShapeData({ 100.0f,100.0f }, "Object/Tree_2")));
	_meshactor2->SetPosition(Vector2f(800.0f, 800.0f));
	

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
