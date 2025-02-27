#include "Game.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "InputManager.h"
#include "CameraManager.h"
#include "CollisionManager.h"

using namespace Camera;

Game::Game()
{
    window = RenderWindow();
}

void Game::Start()
{
    window.create(VideoMode({ 1920, 1080 }), "Tank War", State::Windowed);
    Image _image = Image("Assets/Logo/AppLogo.png");
    window.setIcon(_image);
};

bool Game::Update()
{
    TM_Seconds& _timer = M_TIMER;
    _timer.Update();

    Input::M_INPUT.Update(window);

    const float _deltaTime = _timer.GetDeltaTime().asSeconds();
    M_COLLISION.ResetCollisionPair();
    M_ACTOR.Tick(_deltaTime);

    return IsOver();
}

void Game::UpdateWindow()
{
    window.clear(Color(115, 133, 37));
    M_CAMERA.RenderAllCameras(window);
    window.display();
}

void Game::Stop()
{
    M_ACTOR.BeginDestroy();
}