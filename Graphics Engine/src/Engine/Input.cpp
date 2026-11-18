#include "Input.h"
#include "Window.h"

#include <GLFW/glfw3.h>

void Input::Init(const Window& window)
{
    windowHandle = window.GetHandle();
}

bool Input::IsKeyDown(Key key) const
{
    if (windowHandle == nullptr)
        return false;

    return glfwGetKey(windowHandle, static_cast<int>(key)) == GLFW_PRESS;
}
