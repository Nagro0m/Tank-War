#include "TankCreation.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "HUD.h"
#include "Tank.h"

TankCreation::TankCreation(const int _tankNumber)
{
    tankNumber = _tankNumber;
    tankMenuPosition = Vector2f(-1000.0f * tankNumber, -1000.0f);
    currentStep = 0;
    trackIndex = 0;
    hullIndex = 0;
    weaponIndex = 0;
    tracks = GetTracks();
    hulls = GetHulls();
    weapons = GetWeapons();
    currentActor = nullptr;
}

void TankCreation::Start()
{
    GenerateTankCreationMenu();

    //M_INPUT.BindActionWithState(Code::Q, bind(&TankCreation::PreviousOption, this), true);
    //M_INPUT.BindActionWithState(Code::D, bind(&TankCreation::NextOption, this), true);
    //M_INPUT.BindActionWithState(Code::Enter, bind(&TankCreation::ConfirmSelection, this), true);
    SpawnCurrentSelection();
}

vector<Track> TankCreation::GetTracks()
{
    vector<Track> _tracks;
    const u_int _tracksCount = 4;
    for (u_int _index = 1; _index <= _tracksCount; _index++)
    {
        _tracks.push_back(Track(Vector2f(110, 150.0f), "Tank/Tracks/Track_" + to_string(_index)));
    }
    return _tracks;
}

vector<Hull> TankCreation::GetHulls()
{
    vector<Hull> _hulls;
    const u_int _hullsCount = 8;
    for (u_int _index = 1; _index <= _hullsCount; _index++)
    {
        _hulls.push_back(Hull(Vector2f(150.0f, 150.0f), "Tank/Hulls_" + to_string(tankNumber) + "/Hull_" + to_string(_index)));
    }
    return _hulls;
}

vector<Weapon> TankCreation::GetWeapons()
{
    vector<Weapon> _weapons;
    const u_int _weaponsCount = 8;
    for (u_int _index = 1; _index <= _weaponsCount; _index++)
    {
        _weapons.push_back(Weapon(Vector2f(50.0f, 120.0f), "Tank/Weapons_" + to_string(tankNumber) + "/Gun_" + to_string(_index)));
    }
    return _weapons;
}

void TankCreation::GenerateTankCreationMenu()
{
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _assets =
    {
        {Vector2f(500, 630), "Menu/SelectMenu", Vector2f(0.0f, 0.0f), true, 90.0f},
        {Vector2f(60, 60), "Menu/TankCreation/Cross", Vector2f(-285.0f, -200.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/Validation", Vector2f(8.0f, 170.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/LeftArrow", Vector2f(-200.0f, 75.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/RightArrow", Vector2f(200.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/Button", Vector2f(8.0f, 75.0f), true, 0.0f},
    };
    CameraActor* _camera = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(0.0f, 0.0f), Vector2f(1920.0f, 1080.0f), "TankCreationMenu"));
    for (const auto [_size, _texture, _position, _useMiddleOrigin, _rotation] : _assets)
    {
        Vector2f _adjustedPosition = tankMenuPosition + _position;

        tankMenu.push_back(CreateActors(_size, _texture, _adjustedPosition, _useMiddleOrigin, _rotation));
    }
    menuLabel = UI::M_HUD.CreateWidget<UI::Label>(UI::Label("Chenille", Screen, "Gagalin", OTF));
    menuLabel->SetZOrder(1);
    menuLabel->SetColor(Color::Black);
    menuLabel->SetCharacterSize(30);
    menuLabel->SetOriginAtMiddle();
    menuLabel->SetPosition(tankMenuPosition + Vector2f(10, 50.0f));
    UI::M_HUD.AddToViewport(menuLabel);

    _camera->SetTarget(tankMenu[0]);
    Camera::M_CAMERA.SetCurrent(_camera);

}

void TankCreation::PreviousOption()
{
    RemoveCurrentSelection();

    if (currentStep == 0)
    {
        const int _tracksSize = static_cast<int>(tracks.size());
        trackIndex = (trackIndex - 1 + _tracksSize) % _tracksSize;
    }
    else if (currentStep == 1)
    {
        const int _hullsSize = static_cast<int>(hulls.size());
        hullIndex = (hullIndex - 1 + _hullsSize) % _hullsSize;
    }
    else if (currentStep == 2)
    {
        const int _weaponsSize = static_cast<int>(weapons.size());
        weaponIndex = (weaponIndex - 1 + _weaponsSize) % _weaponsSize;
    }
    SpawnCurrentSelection();
}

void TankCreation::NextOption()
{
    RemoveCurrentSelection();

    if (currentStep == 0)
    {
        const int _tracksSize = static_cast<int>(tracks.size());
        trackIndex = (trackIndex + 1) % _tracksSize;
    }
    else if (currentStep == 1)
    {
        const int _hullsSize = static_cast<int>(hulls.size());
        hullIndex = (hullIndex + 1) % _hullsSize;
    }
    else if (currentStep == 2)
    {
        const int _weaponsSize = static_cast<int>(weapons.size());
        weaponIndex = (weaponIndex + 1) % _weaponsSize;
    }
    SpawnCurrentSelection();
}

void TankCreation::SpawnCurrentSelection()
{
    if (currentStep == 0)
    {
        currentActor = Level::SpawnActor(tracks[trackIndex]);
        currentActor->SetPosition(tankMenuPosition + Vector2f(0.0f, -50.0f));
    }
    else if (currentStep == 1)
    {
        menuLabel->SetString("Blindage");
        currentActor = Level::SpawnActor(hulls[hullIndex]);
        currentActor->SetPosition(tankMenuPosition + Vector2f(0.0f, -50.0f));

    }
    else if (currentStep == 2)
    {
        menuLabel->SetString("Canon");
        currentActor = Level::SpawnActor(weapons[weaponIndex]);
        currentActor->SetPosition(tankMenuPosition + Vector2f(0.0f, -50.0f));
    }
    currentActor->SetOriginAtMiddle();
    currentActor->Rotate(degrees(90));
}

void TankCreation::RemoveCurrentSelection()
{
    if (currentActor)
    {
        tankMenu[0]->RemoveChild(currentActor);
        currentActor->Destroy();
        currentActor = nullptr;
    }
}

void TankCreation::ConfirmSelection()
{
    if (currentStep < 2)
    {
        currentStep++;
        SpawnCurrentSelection();
    }
    else
    {
        FinalizeTank();
    }
}

void TankCreation::FinalizeTank()
{
    //vector<Code> _tank1 =
    //{
    //	Code::Q,
    //	Code::D,
    //	Code::Z,
    //	Code::S,
    //};

    //Tank _tank = Tank(_tank1, "tank", "Player1");
    //_tank.AddChild(Level::SpawnActor(tracks[trackIndex]), AT_SNAP_TO_TARGET);
    //_tank.AddChild(Level::SpawnActor(hulls[hullIndex]), AT_SNAP_TO_TARGET);
    //_tank.AddChild(Level::SpawnActor(weapons[weaponIndex]), AT_SNAP_TO_TARGET);
}