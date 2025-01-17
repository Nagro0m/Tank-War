#include "CoreMinimal.h"
#include "TextureManager.h"
#include "TimerManager.h"
#include "ShapeObject.h"
#include "Game.h"

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); // Detection de fuite de mémoire

}

int main()
{
    InitConfig();

    M_GAME.Launch();

    return EXIT_SUCCESS;
}

