#pragma once
#include "BaseGame.h"

class Game : public BaseGame
{
public:
    void Init() override {}
    void Update() override {}
    void Draw() override
    {
        renderer.DrawBufferTriangle(); // Llamado de prueba
    }
    void DeInit() override {}
};