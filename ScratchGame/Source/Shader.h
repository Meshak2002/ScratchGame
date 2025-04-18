#pragma once
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader(const char* vertPath , const char* fragPath,unsigned int programNum=1);
    ~Shader();
    
    std::string ParseShaderSource(const char* path,unsigned int programNum=1);
    unsigned int CompileShader(unsigned int shaderType, std::string& shaderSource);
    unsigned int CreateShaderProgram(unsigned int vertShader, unsigned int fragShader);
    void UseProgram();
    unsigned int GetUniform(const std::string& u_Name);
    void SetUniform(const std::string& u_varName, float f1, float f2, float f3, float f4);
    void SetUniform(const std::string& u_varName, glm::mat4& u_MVP);
    void SetUniform(const std::string& u_Texture , unsigned int ivalue);
    
    unsigned int vertexShader;
    unsigned int fragShader;
    unsigned int programID;
    std::unordered_map<std::string,unsigned int> cachedUniforms;
};

