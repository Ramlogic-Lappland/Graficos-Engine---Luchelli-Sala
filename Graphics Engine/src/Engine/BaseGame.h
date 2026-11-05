#pragma once

#include "EngineAPI.h"
#include "Window.h"
#include "Renderer.h"
#include "Shape.h"
#include "Camera2D.h"
#include "Input.h"

#include <memory>
#include <vector>

class ENGINE_API BaseGame
{
public:
    BaseGame();
    virtual ~BaseGame();

    // Prevent copying or moving the engine instance for C2280 Error of NULL_ptr
    BaseGame(const BaseGame&) = delete;
    BaseGame& operator=(const BaseGame&) = delete;

    BaseGame(BaseGame&&) = delete;
    BaseGame& operator=(BaseGame&&) = delete;

    bool Startup(int width, int height, const char* title);
    void Run();

protected:
    virtual void OnInit() {}
    virtual void OnUpdate(float deltaTime) {}
    virtual void OnRender() {}
    virtual void OnDeInit() {}

    Camera2D& GetCamera();
    bool GetKey(Key key) const;

    Shape* CreateTriangle(float r, float g, float b);
    Shape* CreateSquare(float r, float g, float b);

    Window window;
    Renderer renderer;
    Camera2D camera;
    Input input;

    std::vector<std::unique_ptr<Entity>> entities;
};