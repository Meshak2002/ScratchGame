#include "VertexArray.h"

#include <GL/glew.h>

VertexArray::VertexArray(unsigned int index)
{
    id = index;
    glGenVertexArrays(1,&id);
    glBindVertexArray(id);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1,&id);
}

void VertexArray::Bind()
{
    glBindVertexArray(id);
}

void VertexArray::UnBind()
{
    glBindVertexArray(0);
}
