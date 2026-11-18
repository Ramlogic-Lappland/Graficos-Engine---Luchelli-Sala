#include "Texture2D.h"

#include <GL/glew.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "ThirdParty/stb_image.h"

Texture2D::~Texture2D()
{
    if (id != 0)
        glDeleteTextures(1, &id);
}

bool Texture2D::LoadFromFile(const std::string& path)
{
    if (id != 0)
    {
        std::cerr << "Texture already loaded: " << path << '\n';
        return false;
    }

    // OpenGl (0,0) UV origin starts at bottom-left corner.
    stbi_set_flip_vertically_on_load(1);

    int channels = 0;
    unsigned char* pixels = stbi_load(
        path.c_str(), &width, &height, &channels, STBI_rgb_alpha
    );

    if (!pixels)
    {
        std::cerr << "Failed to load texture: " << path
            << " (" << stbi_failure_reason() << ")\n";
        width = height = 0;
        return false;
    }

    glGenTextures(1, &id);
    if (id == 0)
    {
        stbi_image_free(pixels);
        width = height = 0;
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // STBI_rgb_alpha always supplies four channels, including for RGB PNG/JPEG.
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0,GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(pixels);
    return true;
}

void Texture2D::Bind(unsigned int slot) const
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id);
}