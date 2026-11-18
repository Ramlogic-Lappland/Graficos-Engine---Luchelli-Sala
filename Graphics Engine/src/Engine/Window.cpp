#include "Window.h"
#include <GLFW/glfw3.h>
#include <iostream>

bool Window::Init(int width, int height, const char* title)
{
    if (!glfwInit())
    {
        std::cout << "Error al inicializar GLFW\n";
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowHandle = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!windowHandle)
    {
        std::cout << "Error al crear la ventana de GLFW\n";
        glfwTerminate();
        return false;
    }

    return true;
}

void Window::SwapBuffers()
{
    if (windowHandle != nullptr)
    {
        glfwSwapBuffers(windowHandle);
    }
}

void Window::GetFramebufferSize(int& width, int& height) const
{
    if (windowHandle)
        glfwGetFramebufferSize(windowHandle, &width, &height);
    else
    {
        width = 0;
        height = 0;
    }
}

bool Window::ShouldClose() const
{
    return glfwWindowShouldClose(windowHandle);
}

void Window::PollEvents()
{
    glfwPollEvents();
}

void Window::Destroy()
{
    if (windowHandle)
    {
        glfwDestroyWindow(windowHandle);
        windowHandle = nullptr;
    }
    glfwTerminate();
}