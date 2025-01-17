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
    IntRect _rect = IntRect(Vector2i(0, 0), Vector2i(88 / 2, 248));
    Vector2f _hullPosition = Vector2f(0.0f, 0.0f);
    Vector2f _trackPosition = _hullPosition + Vector2f(15.0f, 0.0f);
    MeshActor* _trackActor = new MeshActor(Vector2f(22.0f, 120.0f), "Tank/Tracks/Track_1", _rect);
    _trackActor->GetShape()->Move(Vector2f(15, 0));
    MeshActor* _trackActor2 = new MeshActor(Vector2f(22.0f, 120.0f), "Tank/Tracks/Track_1", _rect);
    _trackActor2->GetShape()->Move(_trackPosition * 5.5f);

    int _hullIndex = 1;
    string _hullPath = "Tank/Hulls_1/Hull_";
    Vector2f _sizeHull = Vector2f(120.0f, 120.0f);

    int _weaponIndex = 1;
    string _weaponPath = "Tank/Weapons_1/Gun_";
    Vector2f _sizeWeapon = Vector2f(60.0f, 120.0f);

    bool _isHullEdit = true;

    MeshActor* _hullActor = new MeshActor(_sizeHull, _hullPath + to_string(_hullIndex), _rect);
    _hullActor->GetShape()->Move(_hullPosition);

    MeshActor* _weaponActor = new MeshActor(_sizeWeapon, _weaponPath + to_string(_weaponIndex), _rect);
    _weaponActor->GetShape()->Move(_hullPosition + Vector2f(30.0f, 0.0f));

    while (window.isOpen())
    {
        TM_Seconds& _timer = TM_Seconds::GetInstance();
        _timer.Update();

        while (const optional _event = window.pollEvent())
        {
            if (_event->is<Event::Closed>())
            {
                Stop();
            }
            else if (const Event::KeyPressed* _key = _event->getIf<Event::KeyPressed>())
            {
                if (_key->code == Keyboard::Key::Escape)
                {
                    Stop();
                }
                if (_key->code == Keyboard::Key::D)
                {
                    if (_isHullEdit)
                    {
                        _hullIndex = (_hullIndex % 8) + 1; // Cycle de 1 à 8
                        _hullActor->GetShape()->SetTexture(Texture(_hullPath + to_string(_hullIndex))); // Mise à jour de la texture
                    }
                    else
                    {
                        _weaponIndex = (_weaponIndex % 8) + 1; // Cycle de 1 à 8
                        Texture* _texture = new Texture(_weaponPath + to_string(_weaponIndex));
                        _weaponActor->GetShape()->SetTexture(*_texture); // Mise à jour de la texture

                    }
                }
                if (_key->code == Keyboard::Key::Q)
                {
                    _isHullEdit = !_isHullEdit;
                }
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
    
    Font _font = Font("Assets/Fonts/Cartoon.ttf");

    Text _newText = Text(_font);
    _newText.setString("Tank War");
    _newText.setPosition(Vector2f(windowSize.x / 2.8, 0));
    _newText.setCharacterSize(150);
    _newText.setFillColor(Color::Magenta);

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
    window.draw(_newText);
    window.display();
}

void Game::Stop()
{
    window.close();
}
