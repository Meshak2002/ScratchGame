#pragma once

class VertexBuffer
{
public:
        
        VertexBuffer(float size , void* data , unsigned int drawType);
        ~VertexBuffer();
        void Bind();
        void UnBind();
        const unsigned int& GetBufferID();
        unsigned int id;
};


