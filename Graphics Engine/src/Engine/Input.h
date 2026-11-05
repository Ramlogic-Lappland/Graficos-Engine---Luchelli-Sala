#pragma once

#include "EngineAPI.h"
#include "KeyCodes.h"

class Window;
struct GLFWwindow;

class ENGINE_API Input
{
public:
    void Init(const Window& window);

    bool IsKeyDown(Key key) const;

private:
    GLFWwindow* windowHandle = nullptr;
};