#pragma once

#include "EngineAPI.h"

class Window;
class Shape;
class Camera2D;

class ENGINE_API Renderer
{
public:
    bool Init(Window* window);
    void Shutdown();

    void Clear
    (
        float r = 0.0f,
        float g = 0.0f,
        float b = 0.0f,
        float a = 1.0f
    );

    void ApplyCamera(const Camera2D& camera);
    void Draw(const Shape& shape);

private:
    unsigned int shader = 0;
    int colorLocation = -1;
    int modelLocation = -1;
    int viewLocation = -1;
    int projectionLocation = -1;
};