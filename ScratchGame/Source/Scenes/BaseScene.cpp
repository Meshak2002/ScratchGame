#include "BaseScene.h"

#include "../vendor/imgui/imgui.h"

Scenes::BaseScene::BaseScene()
{
}
Scenes::BaseScene::~BaseScene()
{
}



Scenes::SceneManager::SceneManager() : activeScene(nullptr)
{}
Scenes::SceneManager::~SceneManager()
{
    delete activeScene;
    activeScene=nullptr;
}
void Scenes::SceneManager::RegisterScene(const std::string& sceneName, std::function<Scenes::BaseScene*()> returnScene)
{
    scenes[sceneName] = returnScene;
}
void Scenes::SceneManager::UnRegisterScene(const std::string& sceneName)
{
    scenes.erase(sceneName);
}

std::vector<std::string> Scenes::SceneManager::GetSceneNames()
{
    std::vector<std::string> sceneNames;
    for(auto scene : scenes)
    {
        sceneNames.push_back(scene.first);
    }
    return sceneNames;
}

void Scenes::SceneManager::SetActiveScene(std::string scene)
{
    auto it = scenes.find(scene);
    if(it != scenes.end())
    {
        activeScene = it->second();
    }
}

void Scenes::SceneManager::OnGUI()
{
    ImGui::Begin("Game Scenes");
    for(auto scenename : scenes)
    {
        if(ImGui::Button(scenename.first.c_str()))
        {
            SetActiveScene(scenename.first.c_str());
            //check(activeScene);
            activeScene->BeginPlay();
        }
    }
    ImGui::End();
}

Scenes::BaseScene*& Scenes::SceneManager::GetActiveScene()
{
    return activeScene;
}
