#pragma once
#include "Scene.h"
#include "Graphics/Shader.h"
#include "Graphics/Texture.h"

class DefaultScene : public Scene
{
public:
	DefaultScene();
	DefaultScene(const std::string& name);
	~DefaultScene();
	virtual void update(float dt) override;
	virtual void imgui() override;

private:
	Ref<Shader> shader;
	Ref<Texture> tex;
	unsigned int vao, vbo;
};

