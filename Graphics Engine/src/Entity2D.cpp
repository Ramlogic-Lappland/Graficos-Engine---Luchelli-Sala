#include "Entity2D.h"

Entity2D::Entity2D(): Entity(), posX(1.0f), posY(0.0f), rotation(0.0f), scaleX(1.0f), scaleY(1.0f) { }

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