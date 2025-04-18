#pragma once
#include <memory>
#include "BaseScene.h"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexLayout.h"
#include "../Shader.h"

namespace Scenes
{
    class SimpleRenderer : public BaseScene
    {
    public:
        SimpleRenderer();
        ~SimpleRenderer() override;
        void BeginPlay() override;
        void OnUpdate() override;
        void OnRender() override;
        void OnGUI() override;
        
        // X, Y, R, G, B, A
        float vertexBuffer[36] =
        {
            -0.5f, -0.5f,   0.5f,1,1,1,  // (X, Y, R, G, B, A)
             0.5f, -0.5f,   1,0.5f,1,1,
             0.0f,  0.5f,   1,1,0.5f,1,
            -0.5f,  0.3f,   0,1,0.5f,1,
             0.5f,  0.3f,   1,0.5f,0.5f,1,
             0.0f, -0.8f,    0,0,1,1
        };

        unsigned int indexBuffer[6] =
        {
            0, 2, 1,
            3, 4, 5
        };
        std::unique_ptr<VertexArray> vao; 
        std::unique_ptr<VertexBuffer> vbo;
        std::unique_ptr<IndexBuffer> ibo;
        std::unique_ptr<VertexLayout> vLayout;
        std::unique_ptr<Shader> shader;
        glm::mat4 projection;
        glm::mat4 view;
        glm::mat4 model;
        glm::mat4 mvp;

        float varBlue=0;
        float rotator;
    };
}
