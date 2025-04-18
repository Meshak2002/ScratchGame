#pragma once

class Texture
{
public:
    Texture(const char* path);
    ~Texture();

    void Bind(unsigned int slot);
    void UnBind();
    unsigned int renderId;
    unsigned char* data;
    unsigned int format;
    int width;
    int height;
    int channels;
    
};
