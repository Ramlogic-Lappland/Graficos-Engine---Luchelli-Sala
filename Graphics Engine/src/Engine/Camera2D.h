#pragma once

#include "EngineAPI.h"
#include <glm/glm.hpp>

class ENGINE_API Camera2D
{
public:
    Camera2D();
    ~Camera2D();

    void SetPosition(float x, float y);
    void Move(float dx, float dy);
    void SetRotation(float degrees);
    void SetZoom(float zoom);
    void SetVerticalSize(float worldUnits);
    void SetViewportSize(int width, int height);

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix() const;

    glm::vec2 GetPosition() const { return position; }
    float GetRotation() const { return rotationDegrees; }
    float GetZoom() const { return zoomFactor; }
    float GetVerticalSize() const { return verticalSize; }

private:
    glm::vec2 position{ 0.0f, 0.0f };
    float rotationDegrees = 0.0f;
    float zoomFactor = 1.0f;
    float verticalSize = 3.0f;
    int viewportWidth = 1;
    int viewportHeight = 1;
};
