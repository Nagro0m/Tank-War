#include "TankCreation.h"
#include "ActorManager.h"

Tank::TankCreation::TankCreation()
{
    hullsData = HullsData();
    weaponsData = WeaponsData();

    LoadTankComponents();
}

void Tank::TankCreation::CreateTank()
{
    GenerateTankCreationMenu();

    // Configurer la caméra et le menu
    cameraCreationMenu->SetTarget(creationMenu["Menu/SelectMenu"]);
    //Camera::M_CAMERA.SetCurrent(_tankCamera);

    //HandleWeaponSelection(currentWeaponIndex, weaponsName);
}

// Affiche l'arme en utilisant son sprite et la position spécifiée
void Tank::TankCreation::DisplayWeaponSprite(const Weapon& _weapon, const Vector2f& _position)
{
}

void Tank::TankCreation::HandleWeaponSelection(int& currentWeaponIndex, const vector<string>& weaponsName)
{
    //if (Input::IsKeyPressed(Key::Left))
    //{
    //    currentWeaponIndex = (currentWeaponIndex - 1 + weaponsName.size()) % weaponsName.size();
    //}
    //else if (Input::IsKeyPressed(Key::Right))
    //{
    //    currentWeaponIndex = (currentWeaponIndex + 1) % weaponsName.size();
    //}

    // Supprimer l'ancienne arme
    if (currentWeapon)
    {
        M_ACTOR.RemoveActor(currentWeapon.get());
        currentWeapon.reset();
    }

    // Créer la nouvelle arme
    currentWeapon = weaponsData.GetWeapon(weaponsName[currentWeaponIndex]);
    if (currentWeapon)
    {
        Weapon* _weapon = Level::SpawnActor(*currentWeapon.get());
        _weapon->GetMesh()->GetShape()->Rotate(degrees(90));
        _weapon->GetMesh()->GetShape()->SetPosition(Vector2f(creationMenu["Menu/TankCreation/WeaponButton"]->GetPosition().x,
            creationMenu["Menu/TankCreation/WeaponButton"]->GetPosition().y - 200.0f));
    }
}

void Tank::TankCreation::LoadTankComponents()
{

}

void Tank::TankCreation::GenerateTankCreationMenu()
{
    Vector2f _basePosition = Vector2f(-1000.0f, -1000.0f);
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _assets =
    {
        {Vector2f(500, 630), "Menu/SelectMenu", Vector2f(0.0f, 0.0f), true, 90.0f},
        {Vector2f(60, 60), "Menu/TankCreation/Cross", Vector2f(-285.0f, -200.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/Validation", Vector2f(8.0f, 170.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/LeftArrow", Vector2f(-200.0f, 75.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/RightArrow", Vector2f(200.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/HullButton", Vector2f(8.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/WeaponButton", Vector2f(8.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/TrackButton", Vector2f(8.0f, 75.0f), true, 0.0f},
    };

    // Crée une instance de WeaponsData pour accéder aux données des armes
    WeaponsData weaponsData;

    cameraCreationMenu = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(1280, 720), "TankCamera"));

    // Récupère les armes disponibles pour les afficher
    const vector<string>& weaponsName = weaponsData.GetWeaponsName();

    // Déclaration pour gérer l'index de l'arme actuellement affichée
    int currentWeaponIndex = 0;

    for (const auto [_size, _texture, _position, _useMiddleOrigin, _rotation] : _assets)
    {
        // Ajustement de la taille en fonction de la caméra
        Vector2f cameraSize = cameraCreationMenu->GetScale();
        Vector2f screenSize = Vector2f(1920, 1080);
        float _scaleFactor = cameraSize.x / screenSize.x;
        Vector2f _adjustedPosition = _basePosition + _position;

        if (_texture == "Menu/TankCreation/TrackButton")
        {

        }
        else if (_texture == "Menu/TankCreation/WeaponButton")
        {

            // Affichage de l'arme courante
            shared_ptr<Weapon> _currentWeapon = weaponsData.GetWeapon(weaponsName[currentWeaponIndex]);
            if (_currentWeapon)
            {
                Weapon* _weapon = Level::SpawnActor(*_currentWeapon.get());
                _weapon->GetMesh()->GetShape()->Rotate(degrees(90));
                _weapon->GetMesh()->GetShape()->SetPosition(Vector2f(_adjustedPosition.x, _adjustedPosition.y - 200.0f));
            }
        }
        else if (_texture == "Menu/TankCreation/HullButton")
        {

        }

        // Pour les autres éléments du menu, on garde le comportement classique
        creationMenu[_texture] = CreateActors(_size, _texture, _adjustedPosition, _useMiddleOrigin, _rotation);
        
    }
}