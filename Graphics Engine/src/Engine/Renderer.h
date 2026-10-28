#pragma once

#include "EngineAPI.h"

class Window;
class Shape;

class ENGINE_API Renderer
{
public:
    bool Init(Window& window);
    void Shutdown();

    void Clear
    (
        float r = 0.0f,
        float g = 0.0f,
        float b = 0.0f,
        float a = 1.0f
    );

    void Draw(const Shape& shape);

private:
    unsigned int shader = 0;
    int colorLocation = -1;
};
