#include "Game.h"
#include "GameManager.h"
#include "TankWarGame.h"
#include "FuelGameplay.h"

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Logger::Reset();
}

int main()
{
    InitConfig();
    //M_GAME.Launch(new FuelGameplay());
    M_GAME.Launch(new TankWarGame());

    //unique_ptr _uniquePtr = make_unique<int>(5);
    //shared_ptr _sharedPtr;
    //weak_ptr _weakPtr;
    //RenderWindow _window(VideoMode({ 480, 280 }), "SFML");
    //const Vector2f _windowSize = CAST(Vector2f, _window.getSize());
    //const Vector2f& _size = Vector2f(100.0f, 100.0f);
    //const Vector2f& _position = (Vector2f(_windowSize) / 2.0f - _size / 2.0f);
    ////Le quadrilatère doit tjr rester centré au middle
    ////Il doit se resize automatiquement
    //vector<Vertex> _vertices =
    //{
    //    {Vector2f(_position.x, _position.y), Color::Red},
    //    {Vector2f(_position.x + _size.x, _position.y), Color::Blue},
    //    {Vector2f(_position.x + _size.x, _position.y + _size.y), Color::Red},
    //    {Vector2f(_position.x, _position.y + _size.y), Color::Blue},
    //    {Vector2f(_position.x, _position.y), Color::Red},
    //    {Vector2f(_position.x + _size.x, _position.y + _size.y), Color::Blue},
    //    {Vector2f(_position.x + _size.x, _position.y), Color::Red},
    //    {Vector2f(_position.x, _position.y + _size.y), Color::Blue},
    //};
    //while (_window.isOpen())
    //{
    //    while (const optional _event = _window.pollEvent())
    //    {
    //        if (_event->is<Event::Closed>())
    //        {
    //            _window.close();
    //        }
    //        if (const Event::Resized* _resized = _event->getIf<Event::Resized>())
    //        {
    //            const int _newX = _resized->size.x <= (int)_size.x ? (int)_size.x : _resized->size.x;
    //            const int _newY = _resized->size.x <= (int)_size.x ? (int)_size.x : _resized->size.x;
    //            _window.setSize(Vector2u(_newX, _newY));
    //        }
    //    }
    //    _window.clear();
    //    _window.draw(_vertices.data(), _vertices.size(), PrimitiveType::TriangleStrip);
    //    _window.display();
    //}

	return EXIT_SUCCESS;
}