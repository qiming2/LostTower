#include "GameObject.h"

GameObject::GameObject()
{
}

void GameObject::addComponent(Ref<Component> comp) {
	comp->gameObject = this;
	comps.push_back(comp);
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

void GameObject::onTriggerEnter(Collider2D* other)
{
	kp("OnTriggerEnter Func");
}

void
GameObject::onTrigger(Collider2D* other)
{
	
}

void GameObject::onTriggerExit(Collider2D* other)
{
	kp("OnTriggerExit Func");
}
