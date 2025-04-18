#include "Shader.h"
#include "Shader.h"
#include "Shader.h"

#include <iostream>
#include <GL/glew.h>

#include "fstream"
#include "sstream"

Shader::Shader(const char* vertPath, const char* fragPath,unsigned int programNum)
{
    std::string vertShaderSrc = ParseShaderSource(vertPath,programNum);
    std::string fragShaderSrc = ParseShaderSource(fragPath,programNum);
    vertexShader = CompileShader(GL_VERTEX_SHADER,vertShaderSrc);
    fragShader = CompileShader(GL_FRAGMENT_SHADER,fragShaderSrc);
    programID = CreateShaderProgram(vertexShader,fragShader);
}
Shader::~Shader()
{
    glDeleteProgram(programID);
}

std::string Shader::ParseShaderSource(const char* path,unsigned int programNum)
{
    std::ifstream file(path);
    if(!file)
    {
        std::cerr << "Error: Could not open shader file: " << path << std::endl;
        return "Parsing Shader Failed";
    }
    std::string source;
    std::string contentIterator;
    std::string targetProgram = "#Prog_"+std::to_string(programNum);
    bool canIterate=false;
    while(std::getline(file,contentIterator))
    {
        if(contentIterator==targetProgram)
        {
            canIterate = true;
            continue;
        }
        if(contentIterator=="#Prog_End" && canIterate)
        {
            return source;
        }
        if(canIterate)
            source+=contentIterator + "\n";
    }
    if(canIterate==false)
        std::cerr << "Cant Find Target program Num " << programNum << std::endl;
    else
        std::cerr << "Cant Find #Prog_End" << std::endl;

    __debugbreak();
    return "Parsing Shader Failed";
}

unsigned int Shader::CompileShader(unsigned int shaderType, std::string& shaderSource)
{
    unsigned int shader = glCreateShader(shaderType);
    const char* shaderSrc = shaderSource.c_str();
    glShaderSource(shader,1,&shaderSrc,nullptr);
    glCompileShader(shader);
    char log[512];
    int isSuccess;
    glGetShaderiv(shader,GL_COMPILE_STATUS,&isSuccess);
    if(isSuccess)
        return shader;
    glGetShaderInfoLog(shader,512,NULL,log);
    std::cout<<log;
    __debugbreak();
    return 0;
}

unsigned int Shader::CreateShaderProgram(unsigned int vertShader, unsigned int fragShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program,vertShader);
    glAttachShader(program,fragShader);
    glLinkProgram(program);
    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
    int isSuccess;
    char log[512];
    glGetProgramiv(program,GL_LINK_STATUS,&isSuccess);
    if(isSuccess)
        return program;
    glGetProgramInfoLog(program,512,NULL,log);
    std::cout << "Shader Compilation Error: " << log << std::endl;
    __debugbreak();
    return 0;
}

void Shader::UseProgram()
{
    glUseProgram(programID);
}

unsigned int Shader::GetUniform(const std::string& u_Name)
{
    unsigned int location = glGetUniformLocation(programID,u_Name.c_str());
    if(location==-1)
        std::cout<<"Cant find uniform : "<<u_Name<<std::endl;
    return location;
}

void Shader::SetUniform(const std::string& u_varName, float f1, float f2, float f3, float f4)
{
    unsigned int location ;
    if(cachedUniforms.find(u_varName)!=cachedUniforms.end())
    {
        location = cachedUniforms[u_varName];
    }
    else
    {
        location = GetUniform(u_varName);
        if(location!=-1)
            cachedUniforms.emplace(u_varName,location);
    }
    glUniform4f(location,f1,f2,f3,f4);
}

void Shader::SetUniform(const std::string& u_varName, glm::mat4& u_MVP)
{
    unsigned int location ;
    if(cachedUniforms.find(u_varName)!=cachedUniforms.end())
    {
        location = cachedUniforms[u_varName];
    }
    else
    {
        location = GetUniform(u_varName);
        if(location!=-1)
            cachedUniforms.emplace(u_varName,location);
    }
    glUniformMatrix4fv(location,1,false,&u_MVP[0][0]);
}

void Shader::SetUniform(const std::string& u_Texture, unsigned int ivalue)
{
    unsigned int location ;
    if(cachedUniforms.find(u_Texture)!=cachedUniforms.end())
    {
        location = cachedUniforms[u_Texture];
    }
    else
    {
        location = GetUniform(u_Texture);
        if(location!=-1)
            cachedUniforms.emplace(u_Texture,location);
    }
    glUniform1i(location,ivalue);
}
