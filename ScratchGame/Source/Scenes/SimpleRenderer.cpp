#include "SimpleRenderer.h"
#include <GL/glew.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "../vendor/imgui/imgui.h"

Scenes::SimpleRenderer::SimpleRenderer() : rotator(0)
{
    vao = std::make_unique<VertexArray>(0);
    vbo = std::make_unique<VertexBuffer>(sizeof(float)*36,vertexBuffer,GL_STATIC_DRAW);
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

Scenes::SimpleRenderer::~SimpleRenderer()
{
}

void Scenes::SimpleRenderer::BeginPlay()
{
}

void Scenes::SimpleRenderer::OnUpdate()
{
    if(varBlue<1)
        varBlue+=0.0001;
    else
        varBlue=0;
    rotator+=0.5f;
    model = glm::translate(glm::mat4(1),glm::vec3(640/2,270,0)) * glm::rotate(glm::mat4(1),glm::radians(rotator),glm::vec3(0,0,1)) * glm::scale(glm::mat4(1),glm::vec3(350,300,0));
    mvp = projection * view * model;
}

void Scenes::SimpleRenderer::OnRender()
{
    //shader->SetUniform(std::string("color"),varBlue,1,1-varBlue,1);
    shader->SetUniform("u_MVP",mvp);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void Scenes::SimpleRenderer::OnGUI()
{
    ImGui::Begin("Game HUD");
    ImGui::Text("Simple Renderer_ Test123");
    ImGui::End();
}
