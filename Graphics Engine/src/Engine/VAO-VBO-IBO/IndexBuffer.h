#pragma once
#include "../EngineAPI.h"

class ENGINE_API IndexBuffer
{
public:
    IndexBuffer(const unsigned int* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;

    unsigned int GetCount() const { return count; }

private:
    unsigned int id = 0;
    unsigned int count = 0;
};
