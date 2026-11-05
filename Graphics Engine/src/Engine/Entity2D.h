#pragma once
#include "Entity.h"
#include <glm/glm.hpp>

class ENGINE_API Entity2D : public Entity
{
protected:
    float posX, posY;
    float rotation;
    float scaleX, scaleY;

public:
    Entity2D();
    virtual ~Entity2D() = default;

    void SetPosition(float x, float y);
    void SetRotation(float angle);
    void SetScale(float sx, float sy);

    glm::mat4 GetModelMatrix() const;

    float GetPosX() const { return posX; }
    float GetPosY() const { return posY; }
    float GetRotation() const { return rotation; }
    float GetScaleX() const { return scaleX; }
    float GetScaleY() const { return scaleY; }
};