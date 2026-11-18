#include "Sprite.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <utility>

namespace
{
    constexpr float quadVertices[] = {
        -0.5f, -0.5f, 0.0f, 0.0f,
         0.5f, -0.5f, 1.0f, 0.0f,
         0.5f,  0.5f, 1.0f, 1.0f,
        -0.5f,  0.5f, 0.0f, 1.0f
    };
    constexpr unsigned int quadIndices[] = { 0, 1, 2, 2, 3, 0 };
}

Sprite::Sprite(std::shared_ptr<Texture2D> newTexture)
    : Entity2D(),
    vertexBuffer(quadVertices, sizeof(quadVertices)),
    indexBuffer(quadIndices, 6),
    texture(std::move(newTexture))
{
    vertexArray.Bind();
    vertexBuffer.Bind();
    indexBuffer.Bind();

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));

    vertexArray.Unbind();
    vertexBuffer.Unbind();
}

void Sprite::Update(float deltaTime)
{
    if (activeAnimation.empty())
        return;

    auto found = animations.find(activeAnimation);
    if (found == animations.end())
        return;

    found->second.Update(deltaTime);
    selectedColumn = found->second.GetColumn();
    selectedRow = found->second.GetRow();
}

void Sprite::Draw(Renderer& renderer)
{
    renderer.Draw(*this);
}

void Sprite::SetTint(float r, float g, float b, float a)
{
    tint = glm::vec4(r, g, b, a);
}

bool Sprite::SetSpriteSheet(int columns, int rows)
{
    if (columns < 1 || rows < 1 || !texture ||
        texture->GetWidth() % columns != 0 ||
        texture->GetHeight() % rows != 0)
        return false;

    sheetColumns = columns;
    sheetRows = rows;
    selectedColumn = 0;
    selectedRow = 0;
    activeAnimation.clear();
    animations.clear();

  
    const float frameWidth = static_cast<float>(texture->GetWidth()) / columns;
    const float frameHeight = static_cast<float>(texture->GetHeight()) / rows;
    if (frameHeight > 0.0f)
        SetScale(frameWidth / frameHeight, 1.0f);

    return true;
}

bool Sprite::SetFrame(int column, int row)
{
    if (column < 0 || column >= sheetColumns || row < 0 || row >= sheetRows)
        return false;

    selectedColumn = column;
    selectedRow = row;
    return true;
}

bool Sprite::AddAnimation(const std::string& name, int row, int frameCount,
    float fps, bool loop, int startColumn)
{
    if (name.empty() || row < 0 || row >= sheetRows ||frameCount < 1 || startColumn < 0 || startColumn >= sheetColumns 
        || frameCount > sheetColumns - startColumn || fps <= 0.0f || animations.find(name) != animations.end()) return false;

    animations.emplace(name, Animation(row, startColumn, frameCount, fps, loop));
    return true;
}

bool Sprite::PlayAnimation(const std::string& name, bool restart)
{
    auto found = animations.find(name);
    if (found == animations.end())
        return false;

    if (activeAnimation != name)
    {
        if (!activeAnimation.empty())
        {
            auto previous = animations.find(activeAnimation);
            if (previous != animations.end())
                previous->second.Stop();
        }
        activeAnimation = name;
        restart = true;
    }

    // multiple instances of animarion "name" do not restart animation
    if (restart)
        found->second.Play(true);
    else if (found->second.IsPaused())
        found->second.Resume();

    selectedColumn = found->second.GetColumn();
    selectedRow = found->second.GetRow();
    return true;
}

void Sprite::PauseAnimation()
{
    auto found = animations.find(activeAnimation);
    if (found != animations.end())
        found->second.Pause();
}

void Sprite::ResumeAnimation()
{
    auto found = animations.find(activeAnimation);
    if (found != animations.end())
        found->second.Resume();
}

void Sprite::StopAnimation()
{
    auto found = animations.find(activeAnimation);
    if (found != animations.end())
    {
        found->second.Stop();
        selectedColumn = found->second.GetColumn();
        selectedRow = found->second.GetRow();
    }
    activeAnimation.clear();
}

bool Sprite::IsAnimationFinished() const
{
    auto found = animations.find(activeAnimation);
    return found != animations.end() && found->second.IsFinished();
}

int Sprite::GetCurrentFrame() const
{
    auto found = animations.find(activeAnimation);
    return found == animations.end() ? 0 : found->second.GetCurrentFrame();
}

glm::vec4 Sprite::GetUVRect() const
{
    const float cellWidth = 1.0f / static_cast<float>(sheetColumns);
    const float cellHeight = 1.0f / static_cast<float>(sheetRows);

    // image rows are numbered top down and OpenGL texture V increases botto mup.
    return glm::vec4
    (
        static_cast<float>(selectedColumn) * cellWidth,
        1.0f - static_cast<float>(selectedRow + 1) * cellHeight,
        cellWidth,
        cellHeight
    );
}
