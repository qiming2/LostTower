#include "SceneManager.h"
#include "LevelEditor.h"
#include "DefaultScene.h"

SceneManager* SceneManager::getInstance()
{
    static SceneManager* _instance = new SceneManager();

    return _instance;
}

Ref<Scene> SceneManager::getCurScene()
{
    return getInstance()->curScene;
}

void SceneManager::changeScene(const std::string& sceneName)
{
    // register before change Scene
    for (auto& scene_p: getInstance()->registered_scenes) {
        if (scene_p.first == sceneName) {
            getInstance()->curScene = Ref<Scene>(scene_p.second());
        }
    }
}

std::string SceneManager::getCurSceneName()
{
    return getInstance()->curScene->name();
}

void SceneManager::update(float dt)
{
    getInstance()->curScene->update(dt);
}

void SceneManager::imgui()
{
    getInstance()->curScene->imgui();
}

SceneManager::SceneManager()
    // default Scene : LevelEditor
{
	
}
