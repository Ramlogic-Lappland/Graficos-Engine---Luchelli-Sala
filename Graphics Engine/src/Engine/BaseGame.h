#pragma once

#include "EngineAPI.h"
#include "Window.h"
#include "Renderer.h"
#include "Shape.h"
#include "Sprite.h"
#include "Camera2D.h"
#include "Input.h"
#include "CollisionManager.h"

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

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
    virtual void OnCollision(Entity2D& first, Entity2D& second) {}

    Camera2D& GetCamera();
    bool GetKey(Key key) const;

    Shape* CreateTriangle(float r, float g, float b);
    Shape* CreateSquare(float r, float g, float b);
    Sprite* CreateSprite(const char* path);

    Window window;
    Renderer renderer;
    Camera2D camera;
    Input input;
    CollisionManager collisionManager;

    std::vector<std::unique_ptr<Entity>> entities;
    std::unordered_map<std::string, std::weak_ptr<Texture2D>> textureCache;
};