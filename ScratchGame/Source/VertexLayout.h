#pragma once

class VertexLayout
{
public:
    VertexLayout();
    ~VertexLayout();
    unsigned int index;
    unsigned int pointer;
    unsigned int GetGLSizeOf(unsigned int dataType);
    void AddAttributeArray(unsigned int count, unsigned int dataType, bool isNormalized, unsigned int stride);
    
};