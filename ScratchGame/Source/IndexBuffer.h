#pragma once

class IndexBuffer
{
public:
        
    IndexBuffer(float size , void* data , unsigned int drawType);
    ~IndexBuffer();
    void Bind();
    void UnBind();
    unsigned int id;
};


 