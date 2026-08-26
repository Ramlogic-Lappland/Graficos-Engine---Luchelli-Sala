// BaseGame.h
#pragma once
#include "Window.h"
#include "Renderer.h"

class BaseGame 
{
protected:
    Window window;     // Composición
    Renderer renderer; // Composición

public:
    bool Startup(int width, int height, const char* title);
    void Run();

    // Métodos virtuales para que 'Game' (EXE) los sobrescriba
    virtual void Init() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void DeInit() = 0;
};