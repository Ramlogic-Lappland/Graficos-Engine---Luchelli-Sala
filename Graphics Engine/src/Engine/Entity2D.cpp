#include "Entity2D.h"
#include <glm/gtc/matrix_transform.hpp>
#include <algorithm>
#include <cmath>

Entity2D::Entity2D() : Entity(), posX(0.0f), posY(0.0f), rotation(0.0f), scaleX(1.0f), scaleY(1.0f) {}

void Entity2D::SetPosition(float x, float y)
{
    posX = x;
    posY = y;
}

void Entity2D::SetRotation(float angle)
{
    rotation = angle;
}

void Entity2D::SetScale(float sx, float sy)
{
    scaleX = sx;
    scaleY = sy;
}
glm::mat4 Entity2D::GetModelMatrix() const
{
    glm::mat4 model(1.0f);

    // Order matters: scale locally then rotate and finally translate.
    model = glm::translate(model, glm::vec3(posX, posY, 0.0f));
    model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(scaleX, scaleY, 1.0f));

    return model;
}

void Entity2D::SetCollisionEnabled(bool enabled) { collisionEnabled = enabled; }
bool Entity2D::IsCollisionEnabled() const { return collisionEnabled; }
void Entity2D::SetStaticCollider(bool value) { staticCollider = value; }
bool Entity2D::IsStaticCollider() const { return staticCollider; }
void Entity2D::SetTrigger(bool value) { trigger = value; }
bool Entity2D::IsTrigger() const { return trigger; }

void Entity2D::SetCollisionBox(float width, float height, float offsetX, float offsetY)
{
    if (width <= 0.0f || height <= 0.0f)
        return;
    collisionSize = { width, height };
    collisionOffset = { offsetX, offsetY };
}

AABB Entity2D::GetAABB() const
{
    const float angle = glm::radians(rotation);
    const float c = std::cos(angle);
    const float s = std::sin(angle);

    const glm::vec2 localCenter = { collisionOffset.x * scaleX, collisionOffset.y * scaleY };
    const glm::vec2 center = 
    {
        posX + localCenter.x * c - localCenter.y * s,
        posY + localCenter.x * s + localCenter.y * c
    };

    const float hx = 0.5f * collisionSize.x * std::abs(scaleX);
    const float hy = 0.5f * collisionSize.y * std::abs(scaleY);

    // An axis-aligned enclosure of the rotated local collision rectangle.
    const glm::vec2 extents = { std::abs(c) * hx + std::abs(s) * hy, std::abs(s) * hx + std::abs(c) * hy };
    return { center - extents, center + extents };
}
