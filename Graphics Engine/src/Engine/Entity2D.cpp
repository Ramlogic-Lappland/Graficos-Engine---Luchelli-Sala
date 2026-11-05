#include "Entity2D.h"
#include <glm/gtc/matrix_transform.hpp>

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
