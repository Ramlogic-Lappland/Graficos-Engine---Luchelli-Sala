#pragma once
struct GLFWwindow;

class Window
{
private:
    GLFWwindow* windowHandle = nullptr;

public:
    bool Init(int width, int height, const char* title);
    bool ShouldClose() const;
    void PollEvents();
    void SwapBuffers();
    GLFWwindow* GetHandle() const { return windowHandle; }
    void Destroy();
};