#include "Game.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "TimerManager.h"

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

    while (const optional _event = window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            window.close();
        }
        else if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
        {
            if (_key->code == Keyboard::Key::Up)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(0.0f, -50.0f));
            }
            else if (_key->code == Keyboard::Key::Down)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(0.0f, 50.0f));
            }
            else if (_key->code == Keyboard::Key::Left)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(-50.0f, 0.0f));
            }
            else if (_key->code == Keyboard::Key::Right)
            {
                M_CAMERA.GetCurrent()->Move(Vector2f(50.0f, 0.0f));
            }
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