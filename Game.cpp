#include "Game.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "CameraManager.h"

using namespace Camera;

Game::Game()
{
	window = RenderWindow();
}


void Game::Start()
{
    window.create(VideoMode({ 1920, 1080 }), "Tank War", State::Windowed);
    CameraActor* _camera = M_CAMERA.CreateCamera("Camera");
    _camera->SetScale(CAST(Vector2f, window.getSize()));
    M_CAMERA.SetCurrent(_camera);
};

bool Game::Update()
{
    TM_Seconds& _timer = M_TIMER;
    _timer.Update();

    M_INPUT.ConsumeData(window);

    const float _deltaTime = _timer.GetDeltaTime().asSeconds();
    M_ACTOR.Tick(_deltaTime);

    return IsOver();
}

void Game::UpdateWindow()
{
    window.clear();
    M_CAMERA.RenderAllCameras(window);
    window.display();
}

void Game::Stop()
{
    M_ACTOR.BeginDestroy();
}