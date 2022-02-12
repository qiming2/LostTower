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

Ref<Component> GameObject::getComponentByType(ComponentType type)
{
	for (Ref<Component> cmp : comps) {
		if (cmp->getCompType() == type) {
			return cmp;
		}
	}
	return nullptr;
}

void GameObject::imgui()
{
	ImGui::Begin("GameObject Inspector");
	ImGui::Text("Gameobject test");
	ImGui::End();
}
