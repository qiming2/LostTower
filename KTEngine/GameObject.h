#pragma once
#include <string>
#include "Transform.h"
#include "IMGUI/imgui.h"
#include "Window.h"

class GameObject
{
public:
	GameObject();
	GameObject(const std::string& in_tag);
	~GameObject();

	Transform transform;
	std::string tag;
	
	virtual void update(float dt);

	virtual void imgui();
	
};

