#include "VertexBuffer.h"

#include <GL/glew.h>

VertexBuffer::VertexBuffer(float size , void* data , unsigned int drawType) : id(0)
{
    glGenBuffers(1,&id);
    glBindBuffer(GL_ARRAY_BUFFER,id);
    glBufferData(GL_ARRAY_BUFFER,size,data,drawType);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1,&id);
}

void VertexBuffer::Bind()
{
    glBindBuffer(GL_ARRAY_BUFFER,id);
}

void VertexBuffer::UnBind()
{
    glBindBuffer(GL_ARRAY_BUFFER,0);
}

const unsigned int& VertexBuffer::GetBufferID()
{
    return id;
}
