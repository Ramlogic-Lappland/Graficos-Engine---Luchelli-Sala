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

    windowHandle = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!windowHandle) 
    {
        std::cout << "Error al crear la ventana de GLFW\n";
        glfwTerminate();
        return false;
    }

    return true;
}

bool Window::ShouldClose()
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