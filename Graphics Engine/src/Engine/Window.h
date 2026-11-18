#pragma once

#include "EngineAPI.h"

struct GLFWwindow;

class ENGINE_API Window
{
private:
    GLFWwindow* windowHandle = nullptr;

public:
    bool Init(int width, int height, const char* title);
    bool ShouldClose() const;
    void PollEvents();
    void SwapBuffers();
    void GetFramebufferSize(int& width, int& height) const;
    GLFWwindow* GetHandle() const { return windowHandle; }
    void Destroy();
};