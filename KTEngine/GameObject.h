#pragma once
#include <string>
#include "Transform.h"
#include "IMGUI/imgui.h"
#include "Window.h"
#include "Component.h"

class GameObject
{
public:
	GameObject();
	GameObject(const std::string& in_tag);
	~GameObject();

	Transform transform;
	std::string tag;
	

	Ref<Component> getComponentByType(ComponentType type);
	virtual void addComponent(Ref<Component> comp);
	virtual void update(float dt);
	virtual void imgui();
private:
	std::vector<Ref<Component>> comps;
};

