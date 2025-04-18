#pragma once

class VertexArray
{
public:
    VertexArray(unsigned int index);
    ~VertexArray();
    void Bind();
    void UnBind();
    unsigned int id;
};