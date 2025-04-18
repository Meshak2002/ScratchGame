#include "Perspective.h"

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"
#include "../vendor/imgui/imgui.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexLayout.h"
#include "../Shader.h"

Scenes::Perspective* Scenes::Perspective::instance=nullptr;

Scenes::Perspective::Perspective() : camFrontDirX(0)
{
    instance=this;
    vao = std::make_unique<VertexArray>(0);
    vbo = std::make_unique<VertexBuffer>(sizeof(float)*168,vertexBuffer,GL_STATIC_DRAW);
    ibo = std::make_unique<IndexBuffer>(sizeof(unsigned int)*36,indexBuffer,GL_STATIC_DRAW);
    vLayout = std::make_unique<VertexLayout>();
    unsigned int rowSize = 3*vLayout->GetGLSizeOf(GL_FLOAT)+4*vLayout->GetGLSizeOf(GL_FLOAT);
    vLayout->AddAttributeArray(3, GL_FLOAT,false,rowSize );
    vLayout->AddAttributeArray(4, GL_FLOAT,false, rowSize);
    shader = std::make_unique<Shader>("Source/Vert.glsl","Source/Frag.glsl");
    shader->UseProgram();
    projection = glm::perspective(glm::radians(45.0f),640.0f/480.0f,0.1f,100.0f);
}

Scenes::Perspective::~Perspective()
{
    glDisable(GL_DEPTH_TEST);
}

void Scenes::Perspective::BeginPlay()
{
    window = glfwGetCurrentContext();
    glEnable(GL_DEPTH_TEST);  
    glfwSetCursorPosCallback(window,CursorPosCallback);
    glfwSetMouseButtonCallback(window,MouseButtonCallback);
}

void Scenes::Perspective::OnUpdate()
{
    ProcessInput();
    view =  glm::lookAt(cameraPos,cameraPos+cameraFront,cameraTop);
    model = glm::translate(glm::mat4(1),glm::vec3(0,0,0))
            * glm::rotate(glm::mat4(1),glm::radians(rotY),glm::vec3(0,1,0))
            * glm::scale(glm::mat4(1.0f), glm::vec3(20,20, 10.0f)); 
    mvp = projection * view * model;
    shader->SetUniform("u_MVP",mvp);
}

void Scenes::Perspective::OnRender()
{
    glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
}

void Scenes::Perspective::OnGUI()
{
    ImGui::Begin("Game HUD");
    ImGui::Text("Perspective Scene_ Test123");
    ImGui::SliderFloat("Rot_Y",&rotY,-180,180);
    
    // 👇 Debug Camera Position
    ImGui::Text("Camera Position:");
    ImGui::Text("X: %.2f, Y: %.2f, Z: %.2f", cameraPos.x, cameraPos.y, cameraPos.z);

    // 👇 Debug Camera Front (Rotation Direction)
    ImGui::Text("Camera Front:");
    ImGui::Text("X: %.2f, Y: %.2f, Z: %.2f", cameraFront.x, cameraFront.y, cameraFront.z);
    ImGui::Text("Camera Top:");
    ImGui::Text("X: %.2f, Y: %.2f, Z: %.2f", cameraTop.x, cameraTop.y, cameraTop.z);

    ImGui::End();
}

void Scenes::Perspective::ProcessInput()
{
    if(GLFW_PRESS == glfwGetKey(window,GLFW_KEY_W))
    {
        cameraPos+=cameraFront*mouseSpeed;
    }
    if(GLFW_PRESS == glfwGetKey(window,GLFW_KEY_S))
    {
        cameraPos-=cameraFront*mouseSpeed;
    }
    if(GLFW_PRESS == glfwGetKey(window,GLFW_KEY_Q))
    {
        cameraPos-=cameraTop*mouseSpeed;
    }
    if(GLFW_PRESS == glfwGetKey(window,GLFW_KEY_E))
    {
        cameraPos+=cameraTop*mouseSpeed;
    }
    if(GLFW_PRESS == glfwGetKey(window,GLFW_KEY_A))
    {
        cameraPos-= glm::cross(cameraFront,cameraTop) *mouseSpeed;
    }
    if(GLFW_PRESS == glfwGetKey(window,GLFW_KEY_D))
    {
        cameraPos+= glm::cross(cameraFront,cameraTop) *mouseSpeed;
    }
}

void Scenes::Perspective::CursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
    //if(ImGui::GetIO().WantCaptureMouse) return;
    if(!instance->canMouseRoam)   return;
    if(instance->firstMouse)
    {
        instance->firstMouse=false;
        instance->xLastPos = xpos;
        instance->yLastPos = ypos;
    }
    instance->xOffset = xpos - instance->xLastPos;
    instance->yOffset = instance->yLastPos - ypos;
    instance->xLastPos = xpos;
    instance->yLastPos = ypos;
    instance->camFrontDirX += instance->xOffset * instance->mouseSensitivity;
    instance->camFrontDirY += instance->yOffset * instance->mouseSensitivity;
    instance->cameraFront = glm::vec3(sin(instance->camFrontDirX),cos(instance->camFrontDirY),-1);
}

void Scenes::Perspective::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if(button==GLFW_MOUSE_BUTTON_RIGHT)
    {
        if(action==GLFW_PRESS)
        {
            instance->canMouseRoam=true;
            instance->firstMouse = true;
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);
        }
        else if(action==GLFW_RELEASE)
        {
            instance->canMouseRoam=false;
            glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_NORMAL);
        }
    }
}
