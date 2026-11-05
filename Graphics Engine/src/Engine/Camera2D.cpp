#include "Camera2D.h"

#include <glm/gtc/matrix_transform.hpp>

Camera2D::Camera2D() = default;
Camera2D::~Camera2D() = default;

void Camera2D::SetPosition(float x, float y)
{
    position = glm::vec2(x, y);
}

void Camera2D::Move(float dx, float dy)
{
    position += glm::vec2(dx, dy);
}

void Camera2D::SetRotation(float degrees)
{
    rotationDegrees = degrees;
}

void Camera2D::SetZoom(float zoom)
{
    if (zoom > 0.0f)
        zoomFactor = zoom;
}

void Camera2D::SetVerticalSize(float worldUnits)
{
    if (worldUnits > 0.0f)
        verticalSize = worldUnits;
}

void Camera2D::SetViewportSize(int width, int height)
{
    //keep the last valid aspect ratio beacuse  GLFW reports 0x0 while minimized
    if (width > 0 && height > 0)
    {
        viewportWidth = width;
        viewportHeight = height;
    }
}

glm::mat4 Camera2D::GetViewMatrix() const
{
    glm::mat4 view(1.0f);

    // The camera's inverse transform moves the world in the opposite direction.
    view = glm::rotate(view, glm::radians(-rotationDegrees), glm::vec3(0.0f, 0.0f, 1.0f));
    view = glm::translate(view, glm::vec3(-position.x, -position.y, 0.0f));

    return view;
}

glm::mat4 Camera2D::GetProjectionMatrix() const
{
    const float aspect = static_cast<float>(viewportWidth) / static_cast<float>(viewportHeight);
    const float halfHeight = 0.5f * verticalSize / zoomFactor;
    const float halfWidth = halfHeight * aspect;

    return glm::ortho(-halfWidth, halfWidth, -halfHeight, halfHeight, -1.0f, 1.0f);
}
