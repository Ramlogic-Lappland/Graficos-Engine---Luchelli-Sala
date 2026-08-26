#pragma once

class Renderer; // Temp

class Entity 
{
protected:
    bool active;

public:
    Entity();
    virtual ~Entity() = default;

    virtual void Update(float deltaTime);
    virtual void Draw(Renderer* renderer) = 0; // Método virtual puro para evitar instancias de esta clase

    bool IsActive() { return active; }
    void SetActive(bool state) { active = state; }
};