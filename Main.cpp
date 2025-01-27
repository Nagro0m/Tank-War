#include "Game.h"
#include "GameManager.h"
#include "TankWarGame.h"

void InitConfig()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    Logger::Reset();
}

int main()
{
    InitConfig();
    M_GAME.Launch(new TankWarGame());

	return EXIT_SUCCESS;
}