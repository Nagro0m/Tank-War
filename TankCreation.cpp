#include "TankCreation.h"
#include "ActorManager.h"
#include "InputManager.h"
#include "Tank.h"

Tank::TankCreation::TankCreation()
{
    hullsData = HullsData();
    weaponsData = WeaponsData();
    tank = make_shared<TankActor>();
    currentWeaponIndex = 0;

    LoadTankComponents();
    SetupInputBindings();  // Initialisation des touches
}

void Tank::TankCreation::CreateTank()
{
    GenerateTankCreationMenu();
    RefreshWeaponDisplay();  // Affiche l'arme au démarrage
}

void Tank::TankCreation::SetupInputBindings()
{
    M_INPUT.BindAction(Code::Enter, [&]() {
        tank->AttachPart(Weapon_Part, weaponsData.GetWeapon(weaponsData.GetWeaponsName()[currentWeaponIndex]));
        LOG(Display, "Weapon selected: " + weaponsData.GetWeaponsName()[currentWeaponIndex]);
        }, "Menu_Player1_Valid");
}

void Tank::TankCreation::UpdateWeaponSelection()
{
    const vector<string>& weaponsName = weaponsData.GetWeaponsName();

    M_INPUT.BindAction(Code::Q, [&]()
        {
            currentWeaponIndex = (currentWeaponIndex == 0) ? CAST(int, weaponsName.size()) - 1 : currentWeaponIndex - 1;
            LOG(Display, "Q pressed (bindaction) - Weapon index: " + to_string(currentWeaponIndex));
            RefreshWeaponDisplay();
        }, "Menu_Playe1_Left");

    if (M_INPUT.IsKeyPressed(Code::Q))
    {
        currentWeaponIndex = (currentWeaponIndex == 0) ? CAST(int, weaponsName.size()) - 1 : currentWeaponIndex - 1;
        LOG(Display, "Q pressed - Weapon index: " + to_string(currentWeaponIndex));
        RefreshWeaponDisplay();
    }
    else if (M_INPUT.IsKeyPressed(Code::D))
    {
        currentWeaponIndex = (currentWeaponIndex == CAST(int, weaponsName.size()) - 1) ? 0 : currentWeaponIndex + 1;
        LOG(Display, "D pressed - Weapon index: " + to_string(currentWeaponIndex));
        RefreshWeaponDisplay();
    }
}

void Tank::TankCreation::RefreshWeaponDisplay()
{
    if (currentWeapon)
    {
        M_ACTOR.RemoveActor(currentWeapon.get());
        currentWeapon.reset();
    }

    currentWeapon = weaponsData.GetWeapon(weaponsData.GetWeaponsName()[currentWeaponIndex]);
    if (currentWeapon)
    {
        Weapon* _weapon = Level::SpawnActor(*currentWeapon.get());
        _weapon->GetMesh()->GetShape()->Rotate(degrees(90));
        _weapon->GetMesh()->GetShape()->SetPosition(Vector2f(
            creationMenu["Menu/TankCreation/WeaponButton"]->GetPosition().x,
            creationMenu["Menu/TankCreation/WeaponButton"]->GetPosition().y - 200.0f));
    }
}

void Tank::TankCreation::Update()
{
    UpdateWeaponSelection();
}

Tank::TankActor* Tank::TankCreation::LoadTankComponents()
{
    // Chargement des composants du tank (à implémenter si nécessaire)
    Tank::TankActor* _actor = new TankActor();
    shared_ptr<Hull> _hull = make_shared<Hull>(Vector2f(50.0f, 100.0f), "/Tank/Hulls_1/Hull_2");
    shared_ptr<Weapon> _weapon = make_shared<Weapon>(Vector2f(50.0f, 100.0f), "/Tank/Weapons_1/Gun_1");
    _actor->AttachPart(Hull_Part, _hull);
    _actor->AttachPart(Weapon_Part, _weapon);
    return _actor;
}

void Tank::TankCreation::GenerateTankCreationMenu()
{
    Vector2f _basePosition = Vector2f(-1000.0f, -1000.0f);
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _assets =
    {
        {Vector2f(500, 630), "Menu/SelectMenu", Vector2f(0.0f, 0.0f), true, 90.0f},
        {Vector2f(80, 80), "Menu/TankCreation/LeftArrow", Vector2f(-200.0f, 75.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/RightArrow", Vector2f(200.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/WeaponButton", Vector2f(8.0f, 75.0f), true, 0.0f}
    };

    const vector<string>& _weaponsName = weaponsData.GetWeaponsName();

    for (const auto [_size, _texture, _position, _useMiddleOrigin, _rotation] : _assets)
    {
        Vector2f screenSize = Vector2f(1920, 1080);
        float _scaleFactor = screenSize.x;
        Vector2f _adjustedPosition = _basePosition + _position;

        if (_texture == "Menu/TankCreation/WeaponButton")
        {
            currentWeapon = weaponsData.GetWeapon(_weaponsName[currentWeaponIndex]);
            if (currentWeapon)
            {
                Weapon* _weapon = Level::SpawnActor(*currentWeapon.get());
                _weapon->GetMesh()->GetShape()->Rotate(degrees(90));
                _weapon->GetMesh()->GetShape()->SetPosition(Vector2f(_adjustedPosition.x, _adjustedPosition.y - 200.0f));
            }
        }

        creationMenu[_texture] = CreateActors(_size, _texture, _adjustedPosition, _useMiddleOrigin, _rotation);
    }
}
