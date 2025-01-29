#include "TankCreation.h"
#include "CameraManager.h"

TankCreation::TankCreation()
{
	hullsData = HullsData();
	weaponsData = WeaponsData();

	LoadTankComponents();
}

void TankCreation::CreateTank()
{
    Vector2f _basePosition = Vector2f(-1000.0f, -1000.0f);
    vector<tuple<Vector2f, string, Vector2f, bool, float>> _assets =
    {
        {Vector2f(500, 630), "Menu/SelectMenu", Vector2f(0.0f, 0.0f), true, 90.0f},
        {Vector2f(60, 60), "Menu/TankCreation/Cross", Vector2f(-280.0f, -200.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/Validation", Vector2f(8.0f, 170.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/LeftArrow", Vector2f(-200.0f, 75.0f), true, 0.0f},
        {Vector2f(80, 80), "Menu/TankCreation/RightArrow", Vector2f(200.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/HullButton", Vector2f(8.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/WeaponButton", Vector2f(8.0f, 75.0f), true, 0.0f},
        {Vector2f(300, 100), "Menu/TankCreation/TrackButton", Vector2f(8.0f, 75.0f), true, 0.0f},
    };

    // Crée une instance de WeaponsData pour accéder aux données des armes
    WeaponsData weaponsData;

    CameraActor* _tankCamera = Camera::M_CAMERA.CreateCamera(CameraActor(Vector2f(), Vector2f(960, 540), "TankCamera"));

    // Récupère les armes disponibles pour les afficher
    const vector<string>& weaponsName = weaponsData.GetWeaponsName();

    // Déclaration pour gérer l'index de l'arme actuellement affichée
    int currentWeaponIndex = 0;

    for (const auto [_size, _texture, _position, _useMiddleOrigin, _rotation] : _assets)
    {
        // Ajustement de la taille en fonction de la caméra
        Vector2f cameraSize = _tankCamera->GetScale();
        Vector2f screenSize = Vector2f(1920, 1080);
        float _scaleFactor = cameraSize.x / screenSize.x;
        Vector2f _adjustedPosition = _basePosition + _position;

        if (_texture == "Menu/TankCreation/WeaponButton")
        {
            // On crée un bouton pour chaque arme
            creationMenu.push_back(CreateActors(_size, "Menu/TankCreation/WeaponButton", _adjustedPosition, _useMiddleOrigin, _rotation));

            // Affichage de l'arme courante
            const SubclassOf<Weapon>* _currentWeapon = weaponsData.GetWeapon(weaponsName[currentWeaponIndex]);
            if (_currentWeapon)
            {
                // Affiche le sprite de l'arme courante avec son index
                //DisplayWeaponSprite(*_currentWeapon, _adjustedPosition);
                _currentWeapon->GetObject().SetPosition(Vector2f(_adjustedPosition.x, _adjustedPosition.y - 200.0f));
            }
        }
        else if (_texture == "Menu/TankCreation/HullButton")
        {

        }
        else if (_texture == "Menu/TankCreation/TrackButton")
        {

        }
        else
        {
            // Pour les autres éléments du menu, on garde le comportement classique
            creationMenu.push_back(CreateActors(_size, _texture, _adjustedPosition, _useMiddleOrigin, _rotation));
        }
    }

    // Configurer la caméra et le menu
    _tankCamera->SetTarget(creationMenu[0]);
    Camera::M_CAMERA.SetCurrent(_tankCamera);

    // Pour naviguer entre les armes
    HandleWeaponSelection(currentWeaponIndex, weaponsName);
}

// Affiche l'arme en utilisant son sprite et la position spécifiée
void TankCreation::DisplayWeaponSprite(const SubclassOf<Weapon>& _weapon, const Vector2f& _position)
{
}

// Gère la sélection d'armes avec le défilement (gauche/droite)
void TankCreation::HandleWeaponSelection(int& currentWeaponIndex, const vector<string>& weaponsName)
{
    //if (Input::IsKeyPressed(Key::Left)) // Si la touche de gauche est pressée
    //{
    //    currentWeaponIndex = (currentWeaponIndex - 1 + weaponsName.size()) % weaponsName.size();
    //}
    //else if (Input::IsKeyPressed(Key::Right)) // Si la touche de droite est pressée
    //{
    //    currentWeaponIndex = (currentWeaponIndex + 1) % weaponsName.size();
    //}
}


void TankCreation::LoadTankComponents()
{

}
