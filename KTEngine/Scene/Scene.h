#pragma once
#include <string>
#include "Common.h"

class Scene {
public:
	virtual void update(float dt) {};
	virtual void imgui() {};
	std::string name() { return this->scene_name; }
protected:
	std::string scene_name;
	Scene() {};
};