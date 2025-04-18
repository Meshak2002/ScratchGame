#include "ImageViewer.h"

#include <GL/glew.h>

#include "../Texture.h"
#include "glm/gtc/matrix_transform.hpp"
#include "../vendor/imgui/imgui.h"

Scenes::ImageViewer::ImageViewer() : scale{100,100} , transform{200,200}
{
    vao = std::make_unique<VertexArray>(0);
    vbo = std::make_unique<VertexBuffer>(sizeof(float)*24,vertexBuffer,GL_STATIC_DRAW);
    ibo = std::make_unique<IndexBuffer>(sizeof(unsigned int)*6,indexBuffer,GL_STATIC_DRAW);
    vLayout = std::make_unique<VertexLayout>();
    unsigned int rowSize = 4*vLayout->GetGLSizeOf(GL_FLOAT);
    vLayout->AddAttributeArray(2, GL_FLOAT,false,rowSize );
    vLayout->AddAttributeArray(2, GL_FLOAT,false,rowSize );
    tex = std::make_unique<Texture>("Source/resource/kojima.jpg");
    tex->Bind(0);
    shader = std::make_unique<Shader>("Source/Vert.glsl","Source/Frag.glsl",2);
    shader->UseProgram();
    shader->SetUniform("u_texture",0);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    projection = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
}

Scenes::ImageViewer::~ImageViewer()
{
}

void Scenes::ImageViewer::BeginPlay()
{
}

void Scenes::ImageViewer::OnUpdate()
{
    view = glm::translate(glm::mat4(1),glm::vec3(0.0f,0.0f,0.0f));
    model = glm::translate(glm::mat4(1),glm::vec3(transform[0],transform[1],1)) * glm::scale(glm::mat4(1.0f), glm::vec3(scale[0],scale[1], 1.0f)); 
    mvp = projection * view * model;
}

void Scenes::ImageViewer::OnRender()
{
    shader->SetUniform("u_MVP",mvp);
    shader->SetUniform("u_color",1.0f,1.0f,1.0f,1.0f);
    glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
}

void Scenes::ImageViewer::OnGUI()
{
    ImGui::Begin("Game HUD");
    ImGui::Text("ImageViewer Scene_ Test123");
    ImGui::SliderFloat2("Translate",transform,0,640);
    ImGui::SliderFloat2("Scale",scale,0,800);
    ImGui::End();
}
