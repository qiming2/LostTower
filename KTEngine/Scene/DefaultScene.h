#pragma once
#include "Scene.h"
class DefaultScene : public Scene
{
public:
	DefaultScene();
	DefaultScene(const std::string& name);
	~DefaultScene();
	virtual void update(float dt) override;
	virtual void imgui() override;

private:

};

