#pragma once
#include "Entity.h"

class Entity2D : public Entity
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

    float GetPosX() { return posX; }
    float GetPosY() { return posY; }
    float GetRotation() { return rotation; }
    float GetScaleX() { return scaleX; }
    float GetScaleY() { return scaleY; }
};