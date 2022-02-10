#include "GameObject.h"

GameObject::GameObject()
{
}

GameObject::GameObject(const std::string& in_tag)
{
	tag = in_tag;
}

GameObject::~GameObject()
{
}

void GameObject::update(float dt)
{
	
}

void GameObject::imgui()
{
	ImGui::Begin("GameObject Inspector");
	ImGui::Text("Gameobject test");
	ImGui::End();
}
