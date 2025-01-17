#include "Game.h"
#include "ShapeObject.h"
#include "ActorManager.h"
#include "TimerManager.h"
#include "SoundManager.h"
#include "Logger.h"

Game::Game()
{
	window = RenderWindow();
    charm = nullptr;
}

Game::~Game()
{
}

void Game::Start()
{
    window = RenderWindow(VideoMode({ 600, 300 }), "SFML Demo");

    TM_Milli& _timer = TM_Milli::GetInstance();
    const float _deltaTime = _timer.GetDeltaTime().asSeconds();

    new Timer([&]() {}, Time(5s), true, true);
}

void Game::Update()
{
    float _pitch = 1.0f;
    while (window.isOpen())
    {
        TM_Seconds& _timer = TM_Seconds::GetInstance();
        _timer.Update();

        //Test de l'accélération de l'engine
        SoundSample* _sound = SoundManager::GetInstance().PlaySound("Tank_Engine", MP3);
        _sound->SetVolume(5.0f);
        _sound->SetPitch(_pitch);
        SLEEP(seconds(0.99 - _pitch + 1.0f));

        while (const optional _event = window.pollEvent())
        {
            if (_event->is<Event::Closed>())
            {
                window.close();
            }

            if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>()) 
            {
                if (_key->code == Keyboard::Key::Space)
                {
                    _timer.Pause();
                }
                else if (_key->code == Keyboard::Key::Z)
                {
                    if (_pitch <= 1.9f)
                    {
                    _pitch += 0.1f;
                    }
                    LOG(Warning, "Pitch : " + to_string(_pitch));
                }
                else if (_key->code == Keyboard::Key::S)
                {
                    if (_pitch >= 0.8f)
                    {
                        _pitch -= 0.1f;
                    }
                }
            }
        }
        const float _deltaTime = _timer.GetDeltaTime().asSeconds();
        ActorManager::GetInstance().Tick(_deltaTime);
        LOG(Warning, "Deltatime => " + to_string(_deltaTime));
    }
}

void Game::UpdateWindow()
{
    window.clear();
    //LOG(Error, "Unable to read file");
    for (Actor* _actor : ActorManager::GetInstance().GetAllActors())
    {
        window.draw(*_actor->GetShape()->GetDrawable());
    }
    window.display();
}

void Game::Stop()
{
    //TODO
}

void Game::Launch()
{
	Start();
	Update();
	Stop();
}
