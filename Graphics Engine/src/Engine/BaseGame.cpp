#include "BaseGame.h"

#include <chrono>
#include <memory>
#include <utility>
#include <vector>
#include <iostream>

BaseGame::BaseGame() = default;

BaseGame::~BaseGame() = default;


bool BaseGame::Startup(int width, int height, const char* title)
{
    if (!window.Init(width, height, title))
    {
        std::cerr << "Failed to initialize Window!\n";
        return false;
    }

    if (!renderer.Init(&window))
    {
        std::cerr << "Failed to initialize Renderer!\n";

        renderer.Shutdown();
        window.Destroy();

        return false;
    }

    OnInit();

    return true;
}


void BaseGame::Run()
{
    using Clock = std::chrono::steady_clock;

    auto previousTime = Clock::now();

    while (!window.ShouldClose())
    {
        auto currentTime = Clock::now();

        float deltaTime = std::chrono::duration<float>(
            currentTime - previousTime
        ).count();

        previousTime = currentTime;

        window.PollEvents();

        // KeepDelta
        OnUpdate(deltaTime);

        // Update all active entities
        const size_t updateCount = entities.size();

        for (size_t i = 0; i < updateCount; i++)
        {
            if (entities[i]->IsActive())
            {
                entities[i]->Update(deltaTime);
            }
        }

        renderer.Clear(0.1f, 0.1f, 0.1f, 1.0f);

        // Draw all active entities
        const size_t drawCount = entities.size();

        for (size_t i = 0; i < drawCount; i++)
        {
            if (entities[i]->IsActive())
            {
                entities[i]->Draw(renderer);
            }
        }

        OnRender();

        window.SwapBuffers();
    }

    OnDeInit();

    // Release GPU resources before destroying OpenGL context
    entities.clear();

    renderer.Shutdown();
    window.Destroy();
}


Shape* BaseGame::CreateTriangle(float r, float g, float b)
{
    std::vector<float> vertices =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.0f,  0.5f
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2
    };

    auto shape = std::make_unique<Shape>(
        vertices,
        indices,
        r, g, b
    );

    Shape* result = shape.get();

    entities.push_back(std::move(shape));

    return result;
}


Shape* BaseGame::CreateSquare(float r, float g, float b)
{
    std::vector<float> vertices =
    {
        -0.5f, -0.5f,
         0.5f, -0.5f,
         0.5f,  0.5f,
        -0.5f,  0.5f
    };

    std::vector<unsigned int> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    auto shape = std::make_unique<Shape>
    (
        vertices,
        indices,
        r, g, b
    );

    Shape* result = shape.get();

    entities.push_back(std::move(shape));

    return result;
}