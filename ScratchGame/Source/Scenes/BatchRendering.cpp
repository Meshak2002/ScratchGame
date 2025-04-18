#include "BatchRendering.h"
#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexLayout.h"
#include "../Shader.h"
#include "../vendor/imgui/imgui.h"

Scenes::BatchRendering::BatchRendering() 
{             
    vao = std::make_unique<VertexArray>(0);
    vbo = std::make_unique<VertexBuffer>(sizeof(float)*36,nullptr,GL_DYNAMIC_DRAW);
    vertexBufferID = vbo->GetBufferID();
    ibo = std::make_unique<IndexBuffer>(sizeof(unsigned int)*6,indexBuffer,GL_STATIC_DRAW);
    vLayout = std::make_unique<VertexLayout>();
    unsigned int rowSize = 2*vLayout->GetGLSizeOf(GL_FLOAT)+4*vLayout->GetGLSizeOf(GL_FLOAT);
    vLayout->AddAttributeArray(2, GL_FLOAT,false,rowSize );
    vLayout->AddAttributeArray(4, GL_FLOAT,false, rowSize);
    shader = std::make_unique<Shader>("Source/Vert.glsl","Source/Frag.glsl");
    shader->UseProgram();
    projection = glm::ortho(0.0f,640.0f,0.0f,480.0f,-1.0f,1.0f);
    view = glm::translate(glm::mat4(1),glm::vec3(0,0,0));
}

Scenes::BatchRendering::~BatchRendering()
{
}

void Scenes::BatchRendering::BeginPlay()
{
}

void Scenes::BatchRendering::OnUpdate()
{
    std::vector<float> vertexBuffer =
       {
        -0.5f+x, -0.5f+y,     0.5f,1,1,1,  // (X, Y, R, G, B, A)
         0.5f+x, -0.5f+y,     1,0.5f,1,1,
         0.0f+x,  0.5f+y,     1,1,0.5f,1,
        -0.5f+x2,  0.3f+y2,   0,1,0.5f,1,
         0.5f+x2,  0.3f+y2,   1,0.5f,0.5f,1,
         0.0f+x2, -0.8f+y2,   0,0,1,1
    };
    glBindBuffer(GL_ARRAY_BUFFER,vertexBufferID);
    glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(float)*36,vertexBuffer.data());
    model = glm::translate(glm::mat4(1),glm::vec3(640/2,270,0)) * glm::scale(glm::mat4(1),glm::vec3(110,100,0));
    mvp = projection * view * model;
}

void Scenes::BatchRendering::OnRender()
{
    shader->SetUniform("u_MVP",mvp);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void Scenes::BatchRendering::OnGUI()
{
    ImGui::Begin("Game HUD");
    ImGui::SliderFloat("Tiangle1 X",&x,-50,50);
    ImGui::SliderFloat("Tiangle1 Y",&y,-50,50);
    ImGui::Spacing();
    ImGui::SliderFloat("Tiangle2 X",&x2,-50,50);
    ImGui::SliderFloat("Tiangle2 Y",&y2,-50,50);
    ImGui::Text("Batch Renderer_ Test123");
    ImGui::End();
}
