#include "Game.h"
#include "ShapeObject.h"
#include "ActorManager.h"

Game::Game()
{
	window = RenderWindow();
}

Game::~Game()
{
}

void Game::Start()
{
    window = RenderWindow(VideoMode({ 1920, 1080 }), "Tank War", Style::Resize, State::Fullscreen);
    Actor* _actor = new Actor(100.f, "Tank/Hulls_1/Hull_1.png");
    //ShapeObject* _shape = new ShapeObject(100.f, "None");
    
}

void Game::Update()
{
    while (window.isOpen())
    {
        while (const optional _event = window.pollEvent())
        {

            if (_event->is<Event::Closed>())
                window.close();
        }
        UpdateWindow();
    }
}

void Game::UpdateWindow()
{
    window.clear();
    for (Actor* _actor : ActorManager::GetInstance().GetALlActors())
    {
        window.draw(*_actor->GetShape()->GetDrawable());
    }
    window.display();
}

void Game::Stop()
{
}

void Game::Launch()
{
	Start();
	Update();
	Stop();
}
