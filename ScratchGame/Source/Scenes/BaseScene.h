#pragma once
#include <functional>
#include <string>
#include <unordered_map>

namespace Scenes
{
    class BaseScene
    {
    public :
        BaseScene();
        virtual ~BaseScene();

        virtual void BeginPlay()=0;
        virtual void OnUpdate()=0;
        virtual void OnRender()=0;
        virtual void OnGUI()=0;
        
    };

    class SceneManager
    {
    public:
        SceneManager();
        ~SceneManager();
        
        void RegisterScene(const std::string& sceneName , std::function<Scenes::BaseScene*()> returnScene);
        void UnRegisterScene(const std::string& sceneName);

        std::vector<std::string> GetSceneNames();
        BaseScene*& GetActiveScene();
        void SetActiveScene(std::string scene);

        void OnGUI();
        
    private:
        std::unordered_map<std::string,std::function<Scenes::BaseScene*()> > scenes;
        BaseScene* activeScene;
    };
}
