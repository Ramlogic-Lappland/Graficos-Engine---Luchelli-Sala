#include "Game.h"
#include <cmath>
#include <time.h>
#include <iostream>

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

    sprite1 = CreateSprite("res/sprites/PadoruSprite.png"); // padoru Static

    if (sprite1)
    {
        sprite1->SetPosition(0.0f, 0.0f);
        sprite1->SetRotation(0.0f);
        sprite1->SetTint(1.0f, 1.0f, 1.0f, 1.0f);
        sprite1->SetActive(false); // deactivated to test
    }

    padoruSprite = CreateSprite("res/sprites/PadoruSpriteSheet.png"); // Padoru Animation
    if (!padoruSprite)
    {
        std::cerr << "Could not create Padoru sprite!\n";
        return;
    }

    // Tell the sprite how its atlas is divided before adding animations.
    if (!padoruSprite->SetSpriteSheet(4, 1))
    {
        std::cerr << "Padoru sprite sheet must have 4 equal columns!\n";
        return;
    }

    if (!padoruSprite->AddAnimation("Spin", 0, 4, 6.0f, true))
    {
        std::cerr << "Could not register Spin animation!\n";
        return;
    }

    padoruSprite->SetPosition(0.0f, 0.0f);
    padoruSprite->SetFrame(0, 0); // Idle: display only first frame
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

    // PADORU ANIMATION CODE =======================================
    if (padoruSprite == nullptr)
        return;

    const float speed = 2.0f;

    float dx = 0.0f;
    float dy = 0.0f;

    if (GetKey(Key::W)) dy += 1.0f;
    if (GetKey(Key::S)) dy -= 1.0f;
    if (GetKey(Key::A)) dx -= 1.0f;
    if (GetKey(Key::D)) dx += 1.0f;

    bool isMoving = (dx != 0.0f || dy != 0.0f);

    if (isMoving)
    {
        // Normalize diagonal movement
        float length = std::sqrt(dx * dx + dy * dy);
        dx /= length;
        dy /= length;

        padoruSprite->SetPosition
        (
            padoruSprite->GetPosX() + dx * speed * deltaTime,
            padoruSprite->GetPosY() + dy * speed * deltaTime
        );

        padoruSprite->PlayAnimation("Spin");
    }
    else
    {
        // Stop animation and return to the first frame
        padoruSprite->StopAnimation();
    }
}

void Game::OnRender()
{

}

void Game::OnDeInit()
{

}

