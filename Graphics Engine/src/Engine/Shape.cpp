#include "Shape.h"
#include "../Engine/Renderer.h"

#include <GL/glew.h>

Shape::Shape(const std::vector<float>& vertices,const std::vector<unsigned int>& indices,float r,float g,float b):
    Entity2D(),vertexBuffer(vertices.data(), static_cast<unsigned int>(vertices.size() * sizeof(float))),indexBuffer(indices.data(),
        static_cast<unsigned int>(indices.size())),color{ r, g, b, 1.0f }
{
    vertexArray.Bind();
    vertexBuffer.Bind();
    indexBuffer.Bind();

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        0,
        2,
        GL_FLOAT,
        GL_FALSE,
        2 * sizeof(float),
        nullptr
    );

    vertexArray.Unbind();
    vertexBuffer.Unbind();
}

void Shape::Draw(Renderer& renderer)
{
    renderer.Draw(*this);
}

const VertexArray& Shape::GetVertexArray() const
{
    return vertexArray;
}

const IndexBuffer& Shape::GetIndexBuffer() const
{
    return indexBuffer;
}

const Color& Shape::GetColor() const
{
    return color;
}
