#pragma once
#include "Scene.h"
class LevelEditor : public Scene
{
public:
	LevelEditor();
	LevelEditor(const std::string& name);
	~LevelEditor();
	virtual void update(float dt) override;
	virtual void imgui() override;
	
private:

};

