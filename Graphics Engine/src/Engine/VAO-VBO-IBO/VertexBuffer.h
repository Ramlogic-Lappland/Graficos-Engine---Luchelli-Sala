#pragma once
#include "../EngineAPI.h"

class ENGINE_API VertexBuffer
{
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();

    void Bind() const;
    void Unbind() const;

private:
    unsigned int id = 0;
};