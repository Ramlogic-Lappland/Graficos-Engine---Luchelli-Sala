#include "IndexBuffer.h"
#include <GL/glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data,unsigned int count): count(count)
{
    glGenBuffers(1, &id);

    glBindBuffer(GL_COPY_WRITE_BUFFER, id);

    glBufferData
    (
        GL_COPY_WRITE_BUFFER,
        count * sizeof(unsigned int),
        data,
        GL_STATIC_DRAW
    );

    glBindBuffer(GL_COPY_WRITE_BUFFER, 0);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &id);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IndexBuffer::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}