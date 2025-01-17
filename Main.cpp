#include "CoreMinimal.h"
#include "Game.h"
#include <thread>

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

//float SimulateDeltaTime()
//{
//    static auto _lastTime = chrono::high_resolution_clock::now();
//    auto _currentTime = chrono::high_resolution_clock::now();
//    chrono::duration<float> _elapsed = _currentTime - _lastTime;
//    _lastTime = _currentTime;
//    return _elapsed.count() * 1000.0f;
//}


int main()
{
    InitConfig();

    Game::GetInstance().Launch();

    return EXIT_SUCCESS;
}

//Faire une apparition sur une carte de formes aléatoires.
//Cercle, triangle, carré, rectangle - taille différente, couleure différente, texture différente

//Il apparait, puis lorsqu'il disparait, il tourne sur lui même.
