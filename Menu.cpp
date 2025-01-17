#include "Menu.h"


Menu::Menu()
{
}


void Menu::SetupElements(Vector2u _windowSize)
{
    //BACKBROUND
    MeshActor* _background = new MeshActor(Vector2f(_windowSize.x, _windowSize.y), "Menu/BG/MenuBg");
    // 
    // TANK WAR TITLE


    //BACKGROUND BUTTON
    MeshActor* _bgButton = new MeshActor(Vector2f(_windowSize.x / 4, _windowSize.y / 1.6), "Menu/BgButton");
    _bgButton->GetShape()->SetPosition(Vector2f(_windowSize.x / 2 - _windowSize.x / 8, _windowSize.y / 3));

    // TANK WAR TITLE
    Vector2f _diff = { 0,  static_cast<float>(_windowSize.y) / 9.0f };
    Vector2f _pos = 
    {
        static_cast<float>(_windowSize.x) / 2.4f,
        static_cast<float>(_windowSize.y) / 2.5f - _diff.y
    };

    for (u_int _index = 0; _index < 3; _index++)
    {
        MeshActor* _button = new MeshActor(Vector2f(_windowSize.x / 6, _windowSize.y / 10 ), "Menu/Button/PlayButton");
        _button->GetShape()->SetPosition(_pos + _diff);
        _pos = _button->GetShape()->GetPosition();

    }

}

