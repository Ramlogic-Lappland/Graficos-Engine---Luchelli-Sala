#pragma once
#include "../EngineAPI.h"

class ENGINE_API VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    void Bind() const;
    void Unbind() const;

    unsigned int GetID() const { return id; }

private:
    unsigned int id = 0;
};
