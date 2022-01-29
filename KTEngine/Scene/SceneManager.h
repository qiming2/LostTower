#pragma once
#include <functional>
#include <vector>
#include <utility>
#include <unordered_map>
#include "Common.h"
#include "Scene.h"


class SceneManager
{
public:
	static SceneManager* getInstance();
	static Ref<Scene> getCurScene();
	// Currently only support change scene through scene name
	// in the future might add more functionality
	static void changeScene(const std::string& sceneName);
	
	static std::string getCurSceneName();

	template<typename T> 
	static void registerScene(const std::string& name) {
		kp("Registering ", name);
		getInstance()->registered_scenes.push_back(std::make_pair(name, []() { return new T(); }));
		
	}

	static void update(float dt);
	static void imgui();

private:
	SceneManager();
	Ref<Scene> curScene;
	// currently only hold all scene constructors
	// and construct them when on call
	std::vector<std::pair <std::string, std::function<Scene*()>>> registered_scenes;
};

