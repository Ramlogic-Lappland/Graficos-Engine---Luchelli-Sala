#include "Game.h"

int main()
{
    Game myGame;

    if (!myGame.Startup(860, 620, "Engine Graficos I"))
    {
        return -1;
    }

    myGame.Run();

    return 0;
}