#pragma once
#include <memory>
#include "glm/glm.hpp"

#include "BaseScene.h"

class Texture;
class Shader;
class VertexLayout;
class IndexBuffer;
class VertexBuffer;
class VertexArray;

namespace Scenes
{
    class BatchRendering : public Scenes::BaseScene
    {
    public:
        BatchRendering();
        ~BatchRendering() override;
        
        void BeginPlay() override;
        void OnUpdate() override;
        void OnRender() override;
        void OnGUI() override;
    private:
        float x=1,y=1;
        float x2=1,y2=1;
        // X, Y, R, G, B, A

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
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 mvp;
                        
        unsigned int vertexBufferID;
    };
}
