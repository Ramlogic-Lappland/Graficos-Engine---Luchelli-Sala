#include "Game.h"
#include <cmath>
#include <time.h>

void Game::OnInit()
{
    
    square1 = CreateSquare(0.0f, 0.0f, 1.0f);
    triangle1 = CreateTriangle(1.0f, 0.0f, 0.0f);
    triangle1->SetPosition(-0.9f, 0.0f);
    triangle1->SetScale(0.7f, 0.7f);
    triangle1->SetRotation(15.0f);

    square1->SetPosition(0.9f, 0.0f);
    square1->SetScale(0.7f, 0.7f);

    // Camera uses world units is not normalized
    GetCamera().SetPosition(0.0f, 0.0f);
    GetCamera().SetVerticalSize(3.0f);
    GetCamera().SetZoom(1.0f);
}

void Game::OnUpdate(float deltaTime)
{
    elapsedTime += deltaTime;

    if (square1)
        square1->SetRotation(square1->GetRotation() + 45.0f * deltaTime);

    // back and fort
    GetCamera().SetPosition(std::sin(elapsedTime) * 1.0f, 0.0f);

}

void Game::OnRender()
{

}

void Game::OnDeInit()
{

}
