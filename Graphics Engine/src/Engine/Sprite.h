#pragma once

#include "Entity2D.h"
#include "Texture2D.h"
#include "VAO-VBO-IBO/VertexArray.h"
#include "VAO-VBO-IBO/VertexBuffer.h"
#include "VAO-VBO-IBO/IndexBuffer.h"

#include <glm/vec4.hpp>
#include <memory>

class Renderer;

class ENGINE_API Sprite : public Entity2D
{
public:
    explicit Sprite(std::shared_ptr<Texture2D> texture);
    ~Sprite() override = default;

    void Draw(Renderer& renderer) override;
    void SetTint(float r, float g, float b, float a = 1.0f);

    const glm::vec4& GetTint() const { return tint; }
    const Texture2D& GetTexture() const { return *texture; }
    const VertexArray& GetVertexArray() const { return vertexArray; }
    const IndexBuffer& GetIndexBuffer() const { return indexBuffer; }

private:
    VertexArray vertexArray;
    VertexBuffer vertexBuffer;
    IndexBuffer indexBuffer;
    std::shared_ptr<Texture2D> texture;
    glm::vec4 tint{ 1.0f, 1.0f, 1.0f, 1.0f };
};
