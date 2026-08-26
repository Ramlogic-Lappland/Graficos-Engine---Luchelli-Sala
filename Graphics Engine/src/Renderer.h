#pragma once

class Window;

class Renderer 
{
public:
    bool Init(Window* window);
    void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
    void SwapBuffers(Window* window);

    void DrawLegacyTriangle(); // TEMPORAL
};