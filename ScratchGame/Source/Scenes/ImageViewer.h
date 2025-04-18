#pragma once
#include "BaseScene.h"
#include "memory"
#include "glm/glm.hpp"
#include "../VertexArray.h"
#include "../VertexBuffer.h"
#include "../IndexBuffer.h"
#include "../VertexLayout.h"
#include "../Shader.h"
#include "../Texture.h"

namespace Scenes
{
    class ImageViewer : public Scenes::BaseScene
    {
        public :
            ImageViewer(); 
        ~ImageViewer() override;

        void BeginPlay() override;
        void OnUpdate() override;
        void OnRender() override;
        void OnGUI() override;

    private:
        // X, Y, R, G, B, A
        float vertexBuffer[16] =
        {
            -0.5f, -0.5f,  0 ,0,
             0.5f, -0.5f,  1 ,0,
             -0.5f,  0.5f, 0 ,1,
             0.5f,  0.5f,  1 ,1
        };

        unsigned int indexBuffer[6] =
        {
            0, 1, 2,
            2 , 3, 1
        };
        std::unique_ptr<VertexArray> vao; 
        std::unique_ptr<VertexBuffer> vbo;
        std::unique_ptr<IndexBuffer> ibo;
        std::unique_ptr<VertexLayout> vLayout;
        std::unique_ptr<Shader> shader;
        std::unique_ptr<Texture> tex;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 mvp;

        float transform[2];
        float scale[2];
        
    };
}
