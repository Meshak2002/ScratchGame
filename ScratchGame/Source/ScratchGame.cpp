#include <iostream>
#include <string>
#include "Debugger.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "fstream"
#include "GameHUD.h"
#include "Scenes/BaseScene.h"
#include "Scenes/BatchRendering.h"
#include "Scenes/ImageViewer.h"
#include "Scenes/Perspective.h"
#include "Scenes/SimpleRenderer.h"
#include "Scenes/Translation.h"

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,4);
    glfwWindowHint(GLFW_OPENGL_PROFILE ,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,true);
    GLFWwindow* window =glfwCreateWindow(640,480,"Game Window",nullptr,nullptr);
    glfwMakeContextCurrent(window);
    std::unique_ptr<GameHUD> gameHUD = std::make_unique<GameHUD>(window);
    if(glewInit()==GLEW_OK)
        std::cerr <<"GLEW Initialized"<<std::endl;
    std::unique_ptr<Debugger> debugger = std::make_unique<Debugger>();
    debugger->EnableDebugOutput();

    std::unique_ptr<Scenes::SceneManager> sceneManager = std::make_unique<Scenes::SceneManager>();
    sceneManager->RegisterScene("SimpleScene",[](){return new Scenes::SimpleRenderer();} );
    sceneManager->RegisterScene("TranslationScene",[](){return new Scenes::Translation();} );
    sceneManager->RegisterScene("ImageViewer",[](){return new Scenes::ImageViewer();});
    sceneManager->RegisterScene("BatchRendering",[](){return new Scenes::BatchRendering();});
    sceneManager->RegisterScene("Perspective",[](){return new Scenes::Perspective();});
    
    std::vector<std::string> sceneNames = sceneManager->GetSceneNames();
    Scenes::BaseScene*& activeScene = sceneManager->GetActiveScene();
    
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        gameHUD->NewFrame();
        if(!activeScene)        //Display List of Available Scenes
        {
            sceneManager->OnGUI();
        }
        else                    //Enter into the active Scene
        {
            activeScene->OnUpdate();
            activeScene->OnRender();
            activeScene->OnGUI();
            ImGui::Begin("Game Scenes");
            if(ImGui::Button("Back"))
            {
                delete activeScene;
                activeScene = nullptr;
            }
            ImGui::End();
        }
        gameHUD->RenderFrame();
        
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    std::cout<<"Hello World!"<<std::endl;   
}
