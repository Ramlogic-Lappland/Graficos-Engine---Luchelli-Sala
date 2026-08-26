#pragma once
struct GLFWwindow;

class Window 
{
private:
    GLFWwindow* windowHandle;

public:
    bool Init(int width, int height, const char* title);
    bool ShouldClose();
    void PollEvents();
    GLFWwindow* GetHandle() const { return windowHandle; }
    void Destroy();
};