#include "Game.h"
#include <cmath>
#include <time.h>

void Game::OnInit()
{
    triangle1 = CreateTriangle(1.0f, 0.0f, 0.0f);
    square1 = CreateSquare(0.0f, 0.0f, 1.0f);

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
    const float shapeSpeed = 2.0f;
    const float cameraSpeed = 2.0f;
    const float zoomSpeed = 1.0f;

    // WASD moves the triangle
    glm::vec2 shapeDirection(0.0f);
    if (GetKey(Key::A)) shapeDirection.x -= 1.0f;
    if (GetKey(Key::D)) shapeDirection.x += 1.0f;
    if (GetKey(Key::S)) shapeDirection.y -= 1.0f;
    if (GetKey(Key::W)) shapeDirection.y += 1.0f;

    if (triangle1 && glm::length(shapeDirection) > 0.0f)
    {
        shapeDirection = glm::normalize(shapeDirection);
        triangle1->SetPosition
        (
            triangle1->GetPosX() + shapeDirection.x * shapeSpeed * deltaTime,
            triangle1->GetPosY() + shapeDirection.y * shapeSpeed * deltaTime
        );
    }

    // Arrow keys move camera 
    glm::vec2 cameraDirection(0.0f);
    if (GetKey(Key::Left)) cameraDirection.x -= 1.0f;
    if (GetKey(Key::Right)) cameraDirection.x += 1.0f;
    if (GetKey(Key::Down)) cameraDirection.y -= 1.0f;
    if (GetKey(Key::Up)) cameraDirection.y += 1.0f;

    if (glm::length(cameraDirection) > 0.0f)
    {
        cameraDirection = glm::normalize(cameraDirection);
        GetCamera().Move
        (
            cameraDirection.x * cameraSpeed * deltaTime,
            cameraDirection.y * cameraSpeed * deltaTime
        );
    }

    // E zoom in -  Q zooms out
    float zoomDirection = 0.0f;
    if (GetKey(Key::E)) zoomDirection += 1.0f;
    if (GetKey(Key::Q)) zoomDirection -= 1.0f;

    if (zoomDirection != 0.0f)
    {
        const float newZoom = std::max(0.25f,GetCamera().GetZoom() + zoomDirection * zoomSpeed * deltaTime);
        GetCamera().SetZoom(newZoom);
    }

    if (square1)
        square1->SetRotation(square1->GetRotation() + 45.0f * deltaTime);
}

void Game::OnRender()
{

}

void Game::OnDeInit()
{

}

