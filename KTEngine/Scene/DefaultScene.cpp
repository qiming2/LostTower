#include "DefaultScene.h"
#include "DefaultScene.h"
#include "IMGUI/imgui.h"
#include "Window.h"

DefaultScene::DefaultScene()
{

}

DefaultScene::DefaultScene(const std::string& name)
{
	this->scene_name = name;
}

DefaultScene::~DefaultScene()
{
}

void DefaultScene::update(float dt)
{
	
}

void DefaultScene::imgui()
{
	ImGui::Begin("This is a Default Scene!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", (float)(Window::getFrameRate() * 1000.0f), 1.0f / Window::getFrameRate());
	ImGui::End();
}
