#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define check(x)  if(!x) {          \
std::cout<<"Assertion failed on -"<< #x <<", in "<<__FILE__<<" at line "<<__LINE__<<std::endl; \
__debugbreak(); \
assert(x); }

class Debugger
{
public:
    Debugger();
    static void APIENTRY GlDebugOutput(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length,
                                    const char* message, const void* userParam);
    void EnableDebugOutput();
};
