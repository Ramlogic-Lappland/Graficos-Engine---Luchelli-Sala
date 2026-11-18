#pragma once

#include "Entity2D.h"
#include "Texture2D.h"
#include "Animation.h"
#include "VAO-VBO-IBO/VertexArray.h"
#include "VAO-VBO-IBO/VertexBuffer.h"
#include "VAO-VBO-IBO/IndexBuffer.h"

#include <glm/vec4.hpp>
#include <memory>
#include <string>
#include <unordered_map>

class Renderer;

class ENGINE_API Sprite : public Entity2D
{
public:
    explicit Sprite(std::shared_ptr<Texture2D> texture);
    ~Sprite() override = default;

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;
    Sprite(Sprite&&) = delete;
    Sprite& operator=(Sprite&&) = delete;

    void Update(float deltaTime) override;
    void Draw(Renderer& renderer) override;
    void SetTint(float r, float g, float b, float a = 1.0f);

    // row 0 = top left row
    bool SetSpriteSheet(int columns, int rows);
    bool SetFrame(int column, int row);
    bool AddAnimation(const std::string& name, int row, int frameCount, float fps, bool loop = true, int startColumn = 0);
    bool PlayAnimation(const std::string& name, bool restart = false);
    void PauseAnimation();
    void ResumeAnimation();
    void StopAnimation();
    bool IsAnimationFinished() const;
    int GetCurrentFrame() const;

    glm::vec4 GetUVRect() const;
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

    int sheetColumns = 1;
    int sheetRows = 1;
    int selectedColumn = 0;
    int selectedRow = 0;
    std::unordered_map<std::string, Animation> animations;
    std::string activeAnimation;
};
