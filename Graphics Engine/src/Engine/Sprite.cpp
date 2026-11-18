#include "Sprite.h"
#include "Renderer.h"

#include <GL/glew.h>
#include <utility>

namespace
{
	constexpr float quadVertices[]
	{
		-0.5f, -0.5f, 0.0f, 0.0f,
		 0.5f, -0.5f, 1.0f, 0.0f,
		 0.5f,  0.5f, 1.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f
	};
	constexpr unsigned int quadIndices[] = { 0, 1, 2, 2, 3, 0 };
}

Sprite::Sprite(std::shared_ptr<Texture2D> newTexture) : Entity2D(), vertexBuffer(quadVertices, sizeof(quadVertices)), indexBuffer(quadIndices, 6), texture(std::move(newTexture))
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

void Sprite::Draw(Renderer& renderer)
{
	renderer.Draw(*this);
}

void Sprite::SetTint(float r, float g, float b, float a)
{
	tint = glm::vec4(r, g, b, a);
}
