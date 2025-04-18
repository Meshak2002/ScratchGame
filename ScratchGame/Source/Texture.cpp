#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"
#include <GL/glew.h>

#include "Debugger.h"


Texture::Texture(const char* path)
{
    stbi_set_flip_vertically_on_load(1);
    data = stbi_load(path, &width, &height, &channels, 0);
    glGenTextures(1, &renderId);
    glBindTexture(GL_TEXTURE_2D, renderId);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP_TO_EDGE);
    if(data)
    {
        if (channels == 1)
            format = GL_RED;
        else if (channels == 3)
            format = GL_RGB;
        else if (channels == 4)
            format = GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0,format, width, height, 0,format, GL_UNSIGNED_BYTE,data);
        stbi_image_free(data);
    }
}

Texture::~Texture()
{
    glDeleteTextures(1,&renderId);
}

void Texture::Bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D, renderId);
}

void Texture::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
