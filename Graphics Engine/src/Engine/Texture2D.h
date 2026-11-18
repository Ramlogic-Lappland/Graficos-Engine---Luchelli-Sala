#pragma once

#include "EngineAPI.h"
#include <string>

class ENGINE_API Texture2D
{
public:
    Texture2D() = default;
    ~Texture2D();

    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    Texture2D(Texture2D&&) = delete;
    Texture2D& operator=(Texture2D&&) = delete;

    bool LoadFromFile(const std::string& path);
    void Bind(unsigned int slot = 0) const;

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    bool IsValid() const { return id != 0; }

private:
    unsigned int id = 0;
    int width = 0;
    int height = 0;
};