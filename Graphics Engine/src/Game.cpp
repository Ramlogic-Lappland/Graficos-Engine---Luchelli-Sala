#include "BaseGame.h"

class Game : public BaseGame 
{
public:
    void Init() override {}
    void Update() override {}
    void Draw() override 
    {
        renderer.DrawLegacyTriangle(); // Llamado de prueba
    }
    void DeInit() override {}
};

int main() 
{
    Game myGame;
    if (myGame.Startup(860, 620, "Engine Graficos I")) 
    {
        myGame.Run();
    }
    return 0;
}