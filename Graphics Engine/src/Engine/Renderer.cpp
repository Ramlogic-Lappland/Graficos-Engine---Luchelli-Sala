#include "Renderer.h"
#include <GL/glew.h>

void Renderer::Draw(const Shape& shape)
{
    if (shader == 0)
        return;

    glUseProgram(shader);

    const Color& color = shape.GetColor();

    if (colorLocation != -1)
    {
        glUniform4f(
            colorLocation,
            color.r,
            color.g,
            color.b,
            color.a
        );
    }

    shape.GetVertexArray().Bind();

    glDrawElements(
        GL_TRIANGLES,
        shape.GetIndexBuffer().GetCount(),
        GL_UNSIGNED_INT,
        nullptr
    );

    shape.GetVertexArray().Unbind();

    glUseProgram(0);
}