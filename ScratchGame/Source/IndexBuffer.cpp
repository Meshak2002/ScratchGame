#include "IndexBuffer.h"

#include <GL/glew.h>

IndexBuffer::IndexBuffer(float size , void* data , unsigned int drawType) : id(0)
{
    glGenBuffers(1,&id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,size,data,drawType);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1,&id);
}

void IndexBuffer::Bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,id);
}

void IndexBuffer::UnBind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
