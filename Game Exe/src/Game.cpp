#include "Game.h"

void Game::OnInit()
{
    triangle1 = CreateTriangle(1.0f, 0.0f, 0.0f);
    square1 = CreateSquare(0.0f, 0.0f, 1.0f);
}

void Game::OnUpdate(float deltaTime)
{
}

void Game::OnRender()
{
}

void Game::OnDeInit()
{
}