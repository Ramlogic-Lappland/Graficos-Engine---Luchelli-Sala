#pragma once

class Window;

class Renderer 
{
public:
    unsigned int shader;

    bool Init(Window* window);
    void Clear(float r = 0.0f, float g = 0.0f, float b = 0.0f, float a = 1.0f);
    void SwapBuffers(Window* window);
 
    //TODO: Put Shader Compile, create program and parse here.

    void DrawLegacyTriangle(); // TEMPORAL
    void DrawBufferTriangle();

    void DestroyShaderProgram();
};

