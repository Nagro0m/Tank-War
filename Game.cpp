#include "Game.h"
#include "ActorManager.h"
#include "TriangleActor.h"
#include "SquareActor.h"
#include "CircleActor.h"
#include "SoundManager.h"
#include "TimerManager.h"
#include "SoundSample.h"


Game::Game()
{
    window = RenderWindow();
}

Game::~Game()
{

}

void Game::Launch()
{
    TM_Milli& _timer = TM_Milli::GetInstance();
    const float _deltaTime = _timer.GetDeltaTime().asSeconds();
    LOG(VeryVerbose, "DeltaTime => " + to_string(_deltaTime));
    LOG(Verbose, "DeltaTime => " + to_string(_deltaTime));
    LOG(Log, "DeltaTime => " + to_string(_deltaTime));
    LOG(Display, "DeltaTime => " + to_string(_deltaTime));
    LOG(Warning, "DeltaTime => " + to_string(_deltaTime));
    LOG(Error, "DeltaTime => " + to_string(_deltaTime));
    LOG(Fatal, "DeltaTime => " + to_string(_deltaTime));
    Start();
    Update();
}

void Game::Start()
{
    SquareActor* _actor = new SquareActor(100.0f, "");
    TriangleActor* _actor2 = new TriangleActor(100.0f, "");
    _actor->GetShape()->SetOrigin({ 100.0f / 2, 100.0f / 2 });
    _actor->GetShape()->SetPosition({ 800 / 2, 600 / 2 });

    window.create(VideoMode({ 800, 600 }), "SFML works!");
    M_SOUND.PlaySound("openDoor", WAV);
    new Timer<Seconds>([&]()
        {
            TM_Seconds& _timer = M_TIMER(Seconds);
            const float _deltaTime = _timer.GetDeltaTime().asSeconds();
            LOG(Display, "DeltaTime => " + to_string(_deltaTime));
        }, Time(seconds(2.0f)), true, true);
}

void Game::Update()
{
	while (window.isOpen())
	{
        TM_Seconds& _timer = TM_Seconds::GetInstance();
        _timer.Update();
        while (const std::optional _event = window.pollEvent())
        {
            if (_event->is<Event::Closed>())
            {
                Stop();
            }
        }
        const float _deltaTime = _timer.GetDeltaTime().asSeconds();
        M_ACTOR.Tick(_deltaTime);
        UpdateWindow();
	}
}

void Game::UpdateWindow()
{
    window.clear();
    
    for (pair<u_int, OnRenderWindow> _render : onRenderWindow)
    {
        _render.second(window);
    }

    for (Actor* _actor : ActorManager::GetInstance().GetAllActors())
    {
        if (MeshActor* _meshActor = dynamic_cast<MeshActor*>(_actor))
        {
            //window.draw(*_meshActor->GetShape()->GetDrawable());
        }
    }
    window.display();
}

void Game::Stop()
{
    window.close();
}
