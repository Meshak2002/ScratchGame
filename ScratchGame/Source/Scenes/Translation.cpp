#include "Translation.h"

#include <GL/glew.h>
#include "glm/gtc/matrix_transform.hpp"
#include "../vendor/imgui/imgui.h"

Scenes::Translation::Translation() : scale{100,100} , transform{200,200}
{
    vao = std::make_unique<VertexArray>(0);
    vbo = std::make_unique<VertexBuffer>(sizeof(float)*24,vertexBuffer,GL_STATIC_DRAW);
    ibo = std::make_unique<IndexBuffer>(sizeof(unsigned int)*6,indexBuffer,GL_STATIC_DRAW);
    vLayout = std::make_unique<VertexLayout>();
    unsigned int rowSize = 2*vLayout->GetGLSizeOf(GL_FLOAT)+4*vLayout->GetGLSizeOf(GL_FLOAT);
    vLayout->AddAttributeArray(2, GL_FLOAT,false,rowSize );
    vLayout->AddAttributeArray(4, GL_FLOAT,false, rowSize);
    shader = std::make_unique<Shader>("Source/Vert.glsl","Source/Frag.glsl");
    shader->UseProgram();
    projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
    
}

Scenes::Translation::~Translation()
{
}

void Scenes::Translation::BeginPlay()
{
}

void Scenes::Translation::OnUpdate()
{
    view = glm::translate(glm::mat4(1),glm::vec3(0.0f,0.0f,0.0f));
    model = glm::translate(glm::mat4(1),glm::vec3(transform[0],transform[1],1)) * glm::scale(glm::mat4(1.0f), glm::vec3(scale[0],scale[1], 1.0f)); 
    mvp = projection * view * model;
}

void Scenes::Translation::OnRender()
{
    shader->SetUniform("u_MVP",mvp);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void Scenes::Translation::OnGUI()
{
    ImGui::Begin("Game HUD");
    ImGui::Text("Translation Scene_ Test123");
    ImGui::SliderFloat2("Translate",transform,0,640);
    ImGui::SliderFloat2("Scale",scale,0,800);
    ImGui::End();
}
