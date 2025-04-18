#include "VertexLayout.h"

#include <algorithm>
#include <iostream>
#include <GL/glew.h>

VertexLayout::VertexLayout() : pointer(0) , index(0)
{
}

VertexLayout::~VertexLayout()
{
}

unsigned int VertexLayout::GetGLSizeOf(unsigned int dataType)
{
    switch(dataType)
    {
    case GL_FLOAT:
        return sizeof(float);
    case GL_UNSIGNED_INT:
        return sizeof(unsigned int);
    case GL_INT:
        return sizeof(int);
    default:
        __debugbreak();        
        std::cout<<"Can't find the size of the DataType"<<std::endl;
        return 0;
    }
    
}

void VertexLayout::AddAttributeArray(unsigned int count, unsigned int dataType, bool isNormalized, unsigned int stride)
{
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index,count,dataType,isNormalized,stride,(void*)pointer);
    pointer += GetGLSizeOf(dataType) * count;
    index++;
}
