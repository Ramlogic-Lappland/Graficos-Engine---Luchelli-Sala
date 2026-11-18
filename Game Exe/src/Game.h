#pragma once

#include "BaseGame.h"

class Game : public BaseGame
{
protected:
    void OnInit() override;
    void OnUpdate(float deltaTime) override;
    void OnRender() override;
    void OnDeInit() override;

private:
    Sprite* sprite1 = nullptr;
    Shape* triangle1 = nullptr;
    Shape* square1 = nullptr;
    float elapsedTime = 0.0f;
};