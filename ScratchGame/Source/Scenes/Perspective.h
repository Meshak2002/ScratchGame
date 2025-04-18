#pragma once
#include "BaseScene.h"
#include "glm/glm.hpp"
#include "memory"
#include "../vendor/imgui/imgui_impl_glfw.h"

class Shader;
class VertexLayout;
class IndexBuffer;
class VertexBuffer;
class VertexArray;

namespace Scenes
{
    class Perspective : public BaseScene
    {
    public:
        Perspective();
        ~Perspective() override;

        void BeginPlay() override;
        void OnUpdate() override;
        void OnRender() override;
        void OnGUI() override;
        static Perspective* instance;
        
    private:
        // X, Y, R, G, B, A
        float vertexBuffer[168] = {
            // Front face
            -0.5f, -0.5f,  0.5f,   1, 0, 0, 1,
             0.5f, -0.5f,  0.5f,   1, 0, 0, 1,
             0.5f,  0.5f,  0.5f,   1, 0, 0, 1,
            -0.5f,  0.5f,  0.5f,   1, 0, 0, 1,

            // Back face
            -0.5f, -0.5f, -0.5f,   0, 1, 0, 1,
             0.5f, -0.5f, -0.5f,   0, 1, 0, 1,
             0.5f,  0.5f, -0.5f,   0, 1, 0, 1,
            -0.5f,  0.5f, -0.5f,   0, 1, 0, 1,

            // Left face
            -0.5f, -0.5f, -0.5f,   0, 0, 1, 1,
            -0.5f, -0.5f,  0.5f,   0, 0, 1, 1,
            -0.5f,  0.5f,  0.5f,   0, 0, 1, 1,
            -0.5f,  0.5f, -0.5f,   0, 0, 1, 1,

            // Right face
             0.5f, -0.5f, -0.5f,   1, 1, 0, 1,
             0.5f, -0.5f,  0.5f,   1, 1, 0, 1,
             0.5f,  0.5f,  0.5f,   1, 1, 0, 1,
             0.5f,  0.5f, -0.5f,   1, 1, 0, 1,

            // Top face
            -0.5f,  0.5f, -0.5f,   1, 0, 1, 1,
             0.5f,  0.5f, -0.5f,   1, 0, 1, 1,
             0.5f,  0.5f,  0.5f,   1, 0, 1, 1,
            -0.5f,  0.5f,  0.5f,   1, 0, 1, 1,

            // Bottom face
            -0.5f, -0.5f, -0.5f,   0, 1, 1, 1,
             0.5f, -0.5f, -0.5f,   0, 1, 1, 1,
             0.5f, -0.5f,  0.5f,   0, 1, 1, 1,
            -0.5f, -0.5f,  0.5f,   0, 1, 1, 1,
        };

        unsigned int indexBuffer[36] = {
            // Front face
            0, 1, 2, 2, 3, 0,
            // Back face
            4, 5, 6, 6, 7, 4,
            // Left face
            8, 9, 10, 10, 11, 8,
            // Right face
            12, 13, 14, 14, 15, 12,
            // Top face
            16, 17, 18, 18, 19, 16,
            // Bottom face
            20, 21, 22, 22, 23, 20
        };
        GLFWwindow* window;
        std::unique_ptr<VertexArray> vao; 
        std::unique_ptr<VertexBuffer> vbo;
        std::unique_ptr<IndexBuffer> ibo;
        std::unique_ptr<VertexLayout> vLayout;
        std::unique_ptr<Shader> shader;
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 mvp;

        glm::vec3 cameraPos  = glm::vec3(0,0,50);
        glm::vec3 cameraTop  = glm::vec3(0,1,0);
        glm::vec3 cameraFront= glm::vec3(0,0,-1);
        float rotY;
        
        float camFrontDirX=0;
        float camFrontDirY=0;
        const float radius = 50.0f;
        const float mouseSpeed = .01f;
        void ProcessInput();
        
        static void CursorPosCallback(GLFWwindow* window, double xpos, double ypos);
        static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        bool firstMouse=true;
        bool canMouseRoam;
        float mouseSensitivity=0.001f;
        float xLastPos=0;
        float yLastPos=0;
        double xOffset=0;
        double yOffset=0;
    };
}
