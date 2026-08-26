#include "Renderer.h"
#include "Window.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

bool Renderer::Init(Window* window) 
{
    // 1. Vincular el contexto de OpenGL al hilo actual
    glfwMakeContextCurrent(window->GetHandle());

    // 2. Inicializar GLEW para cargar los punteros de funciones de OpenGL
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) 
    {
        std::cout << "Error al inicializar GLEW\n";
        return false;
    }

    // 3. Configurar el Viewport
    int width, height;
    glfwGetFramebufferSize(window->GetHandle(), &width, &height);
    glViewport(0, 0, width, height);

    return true;
}

void Renderer::Clear(float r, float g, float b, float a) 
{
    glClearColor(r, g, b, a);
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffers(Window* window) 
{
    glfwSwapBuffers(window->GetHandle());
}

void Renderer::DrawLegacyTriangle() 
{
    glBegin(GL_TRIANGLES);
    glVertex2f(-0.5f, -0.5f);
    glVertex2f(0.0f, 0.5f);
    glVertex2f(0.5f, -0.5f);
    glEnd();
}