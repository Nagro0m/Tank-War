#include "Game.h"
#include "ActorManager.h"
#include "TriangleActor.h"
#include "SquareActor.h"
#include "CircleActor.h"
#include "SoundManager.h"
#include "TimerManager.h"
#include "SoundSample.h"
#include "Menu.h"


Game::Game()
{
    window = RenderWindow();
    windowSize = { 1920, 1080 };
}

Game::~Game()
{

}

void Game::Launch()
{
    Menu _menu;
    _menu.SetupElements(windowSize);

    Start();
    Update();
}

void Game::Start()
{
    window.create(VideoMode({ windowSize.x, windowSize.y }), "SFML works!", State::Fullscreen);
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
        cout << "X : " << Mouse::getPosition(window).x << " Y : " << Mouse::getPosition(window).y << endl;
        SLEEP(500ms);
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
            window.draw(*_meshActor->GetShape()->GetDrawable());
        }
    }
    window.display();
}

void Game::Stop()
{
    window.close();
}
