#pragma once
#include "Entity.h"
#include <glm/glm.hpp>

struct AABB
{
    glm::vec2 min;
    glm::vec2 max;
};

class ENGINE_API Entity2D : public Entity
{
protected:
    float posX, posY;
    float rotation;
    float scaleX, scaleY;
    float weight = 1.0f;

    bool collisionEnabled = false;
    bool staticCollider = false;
    bool trigger = false;
    glm::vec2 collisionSize{ 1.0f, 1.0f };
    glm::vec2 collisionOffset{ 0.0f, 0.0f };


public:
    Entity2D();
    virtual ~Entity2D() = default;

    void SetPosition(float x, float y);
    void SetRotation(float angle);
    void SetScale(float sx, float sy);

    glm::mat4 GetModelMatrix() const;

    // Collision uses world-space AABBs, independent of rendering.
    void SetCollisionEnabled(bool enabled);
    bool IsCollisionEnabled() const;
    void SetStaticCollider(bool value);
    bool IsStaticCollider() const;
    void SetTrigger(bool value);
    bool IsTrigger() const;
    void SetCollisionBox(float width, float height, float offsetX = 0.0f, float offsetY = 0.0f);
    AABB GetAABB() const;

    float GetPosX() const { return posX; }
    float GetPosY() const { return posY; }
    float GetRotation() const { return rotation; }
    float GetScaleX() const { return scaleX; }
    float GetScaleY() const { return scaleY; }

    void SetWeight(float value)
    {
        weight = value > 0.0f ? value : 1.0f;
    }

    float GetWeight() const
    {
        return weight;
    }
};