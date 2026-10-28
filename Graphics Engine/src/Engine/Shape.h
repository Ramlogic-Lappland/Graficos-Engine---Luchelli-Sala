#pragma once

#include "Entity2D.h"
#include "../Engine/VAO-VBO-IBO/VertexArray.h"
#include "../Engine/VAO-VBO-IBO/VertexBuffer.h"
#include "../Engine/VAO-VBO-IBO/IndexBuffer.h"

#include <vector>

class Renderer;

struct Color
{
    float r;
    float g;
    float b;
    float a;
};

class ENGINE_API Shape : public Entity2D
{
public:
    Shape(
        const std::vector<float>& vertices,
        const std::vector<unsigned int>& indices,
        float r,
        float g,
        float b
    );

    ~Shape() override = default;

    void Draw(Renderer& renderer) override;

    const VertexArray& GetVertexArray() const;
    const IndexBuffer& GetIndexBuffer() const;
    const Color& GetColor() const;

private:
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;

    Color color;
};
