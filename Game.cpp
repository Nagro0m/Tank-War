#include "Game.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "TimerManager.h"
#include "HUD.h"
#include "Label.h"

using namespace Camera;
using namespace UI;

Game::Game()
{
	window = RenderWindow();
}


void Game::Start()
{
    window.create(VideoMode({ 1920, 1080 }), "Tank War", State::Windowed);

    M_CAMERA.CreateCamera(Vector2f(), Vector2f(800.0f, 600.0f), "DefaultCamera");

    Label* _label = M_HUD.CreateWidget<Label>("Coucou", World);
    _label->SetZOrder(1);
    M_HUD.AddToViewport(_label);
};

bool Game::Update()
{
    TM_Seconds& _timer = M_TIMER;
    _timer.Update();

    while (const optional _event = window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            window.close();
        }
    }

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