#include "BaseGame.h"

bool BaseGame::Startup(int width, int height, const char* title) 
{
    // Composición: BaseGame gestiona la creación del ciclo de vida de Window y Renderer
    if (!window.Init(width, height, title)) return false;
    if (!renderer.Init(&window)) return false;

    Init(); // Inicialización propia del juego cliente (EXE)
    return true;
}

void BaseGame::Run() 
{
    while (!window.ShouldClose()) 
    {
        window.PollEvents();     // 1. Procesar Entradas de la SO

        Update();                // 2. Actualizar Lógica del Juego

        renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f); // 3. Limpiar frame anterior
        Draw();                  // 4. Dibujar Entidades
        renderer.SwapBuffers(&window);
    }

    DeInit();
    window.Destroy();
}