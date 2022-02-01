#include "LevelEditor.h"
#include "IMGUI/imgui.h"
#include "Window.h"
#include "Graphics/Shader.h"

LevelEditor::LevelEditor()
{
	
}

LevelEditor::LevelEditor(const std::string& name)
{
	this->scene_name = name;
}

LevelEditor::~LevelEditor()
{
}

void LevelEditor::update(float dt)
{

}

void LevelEditor::imgui()
{
	ImGui::Begin("This is a Level Editor Scene");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", (float)Window::getFrameRate() * 1000.0f, 1.0f / Window::getFrameRate());
	ImGui::End();
}
