#pragma once

#include "EngineAPI.h"

class Renderer;

class ENGINE_API Entity
{
protected:
    bool active;

public:
    Entity();
    virtual ~Entity() = default;

    virtual void Update(float deltaTime);
    virtual void Draw(Renderer& renderer) = 0;

    bool IsActive() const { return active; }
    void SetActive(bool state) { active = state; }
};