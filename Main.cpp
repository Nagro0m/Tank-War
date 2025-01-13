#include "CoreMinimal.h"
#include "Game.h"

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

int main()
{
    InitConfig();

    Game::GetInstance().Launch();

    //RenderWindow _window(VideoMode({ 200, 200 }), "SFML Demo");
    //ShapeObject* _shape = new ShapeObject(100.f, "Mario.png");
    //SLEEP(50ms);
    //while (_window.isOpen())
    //{
    //    while (const optional _event = _window.pollEvent())
    //    {
    //        if (_event->is<Event::Closed>())
    //            _window.close();
    //    }
    //    _window.clear();
    //    _window.draw(*_shape->GetDrawable());
    //    _window.display();
    //}
    //delete _shape;

    return EXIT_SUCCESS;
}